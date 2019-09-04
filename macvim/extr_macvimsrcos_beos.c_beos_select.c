#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct fd_set {int dummy; } ;
typedef  int /*<<< orphan*/  bigtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  snooze (scalar_t__) ; 

int
beos_select(int nbits,
       struct fd_set *rbits,
       struct fd_set *wbits,
       struct fd_set *ebits,
       struct timeval *timeout)
{
    bigtime_t tmo;

    if (nbits == 0) {
	/* select is purely being used for delay */
	snooze(timeout->tv_sec * 1e6 + timeout->tv_usec);
	return 0;
    }
#if 0
    /*
     * This does not seem to work either. Reads here are not supposed to
     * block indefinitely, yet they do. This is most annoying.
     */
    if (FD_ISSET(0, rbits)) {
	char cbuf[1];
	int count;
	struct termios told;
	struct termios tnew;
	tcgetattr(0, &told);
	tnew = told;
	tnew.c_lflag &= ~ICANON;
	tnew.c_cc[VMIN] = 0;
	tnew.c_cc[VTIME] = timeout->tv_sec * 10 + timeout->tv_usec / 100000;
	tcsetattr(0, TCSANOW, &tnew);

	count = read(0, &cbuf, sizeof(cbuf));
	tcsetattr(0, TCSANOW, &told);
	if (count > 0) {
	    add_to_input_buf(&cbuf[0], count);
	    return 1;
	}
	return 0;
    }
#endif
#if USE_THREAD_FOR_INPUT_WITH_TIMEOUT
    /*
     * Check if the operation is really on stdin...
     */
    if (FD_ISSET(read_cmd_fd, rbits))
    {
	int acquired;

	/*
	 * Is this the first time through?
	 * Then start up the thread and initialise the semaphores.
	 */
	if (character_present == 0) {
	    character_present = create_sem(0, "vim character_present");
	    character_wanted = create_sem(1, "vim character_wanted");
	    read_thread_id = spawn_thread(read_thread, "vim async read",
		    B_NORMAL_PRIORITY, NULL);
	    atexit(beos_cleanup_read_thread);
	    resume_thread(read_thread_id);
	}

	/* timeout == NULL means "indefinitely" */
	if (timeout) {
	    tmo = timeout->tv_sec * 1e6 + timeout->tv_usec;
	    /* 0 means "don't wait, which is impossible to do exactly. */
	    if (tmo == 0)
		tmo = 1.0;
	}
#if TRY_ABORT
	release_sem(character_wanted);
#endif
	if (timeout)
	    acquired = acquire_sem_etc(character_present, 1, B_TIMEOUT, tmo);
	else
	    acquired = acquire_sem(character_present);
	if (acquired == B_NO_ERROR) {
	    if (charcount > 0) {
		add_to_input_buf(&charbuf, 1);
#if !TRY_ABORT
		release_sem(character_wanted);
#endif

		return 1;
	    } else {
#if !TRY_ABORT
		release_sem(character_wanted);
#endif

		return 0;
	    }
	}
#if TRY_ABORT
	else {
	    /*
	     * Timeout occurred. Break the read() call by sending
	     * a signal. Problem: it may be just read()ing it now.
	     * Therefore we still have to finish the handshake with
	     * the thread and maybe remember the character.
	     */
	    kill(read_thread_id, SIGUSR1);
	    /*
	     *	If some other error occurred, don't hang now.
	     * (We will most likely hang later anyway...)
	     */
	    if (acquired == B_TIMED_OUT)
		acquire_sem(character_present);
	    if (charcount > 0) {
		add_to_input_buf(&charbuf, 1);
		return 1;
	    }
	    return 0;
	}
#endif
    }
#endif

    return 0;
}