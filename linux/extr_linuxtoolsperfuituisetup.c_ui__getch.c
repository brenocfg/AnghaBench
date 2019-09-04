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
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int K_ERROR ; 
 int K_ESC ; 
 int K_RESIZE ; 
 int K_TIMER ; 
 int SLang_getkey () ; 
 int /*<<< orphan*/  SLang_ungetkey (int) ; 
 int SLkp_getkey () ; 
 scalar_t__ errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  ui__setup_sigwinch () ; 

int ui__getch(int delay_secs)
{
	struct timeval timeout, *ptimeout = delay_secs ? &timeout : NULL;
	fd_set read_set;
	int err, key;

	ui__setup_sigwinch();

	FD_ZERO(&read_set);
	FD_SET(0, &read_set);

	if (delay_secs) {
		timeout.tv_sec = delay_secs;
		timeout.tv_usec = 0;
	}

        err = select(1, &read_set, NULL, NULL, ptimeout);

	if (err == 0)
		return K_TIMER;

	if (err == -1) {
		if (errno == EINTR)
			return K_RESIZE;
		return K_ERROR;
	}

	key = SLang_getkey();
	if (key != K_ESC)
		return key;

	FD_ZERO(&read_set);
	FD_SET(0, &read_set);
	timeout.tv_sec = 0;
	timeout.tv_usec = 20;
        err = select(1, &read_set, NULL, NULL, &timeout);
	if (err == 0)
		return K_ESC;

	SLang_ungetkey(key);
	return SLkp_getkey();
}