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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct sigaction {int /*<<< orphan*/  sa_sigaction; void* sa_flags; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 void* SA_SIGINFO ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 scalar_t__ exit_from_pong ; 
 int fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_htm () ; 
 int le ; 
 int /*<<< orphan*/  ping ; 
 int /*<<< orphan*/  pong ; 
 int /*<<< orphan*/  pr_error (int,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setaffinity_np (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 scalar_t__ success ; 
 int /*<<< orphan*/  t0_ping ; 
 int /*<<< orphan*/  t1_pong ; 
 int /*<<< orphan*/  trap_signal_handler ; 
 int /*<<< orphan*/  usr1_signal_handler ; 

int tm_trap_test(void)
{
	uint16_t k = 1;

	int rc;

	pthread_attr_t attr;
	cpu_set_t cpuset;

	struct sigaction trap_sa;

	SKIP_IF(!have_htm());

	trap_sa.sa_flags = SA_SIGINFO;
	trap_sa.sa_sigaction = trap_signal_handler;
	sigaction(SIGTRAP, &trap_sa, NULL);

	struct sigaction usr1_sa;

	usr1_sa.sa_flags = SA_SIGINFO;
	usr1_sa.sa_sigaction = usr1_signal_handler;
	sigaction(SIGUSR1, &usr1_sa, NULL);

	/* Set only CPU 0 in the mask. Both threads will be bound to cpu 0. */
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);

	/* Init pthread attribute */
	rc = pthread_attr_init(&attr);
	if (rc)
		pr_error(rc, "pthread_attr_init()");

	/*
	 * Bind thread ping() and pong() both to CPU 0 so they ping-pong and
	 * speed up context switches on ping() thread, speeding up the load_fp
	 * and load_vec overflow.
	 */
	rc = pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
	if (rc)
		pr_error(rc, "pthread_attr_setaffinity()");

	/* Figure out the machine endianness */
	le = (int) *(uint8_t *)&k;

	printf("%s machine detected. Checking if endianness flips %s",
		le ? "Little-Endian" : "Big-Endian",
		"inadvertently on trap in TM... ");

	rc = fflush(0);
	if (rc)
		pr_error(rc, "fflush()");

	/* Launch ping() */
	rc = pthread_create(&t0_ping, &attr, ping, NULL);
	if (rc)
		pr_error(rc, "pthread_create()");

	exit_from_pong = 0;

	/* Launch pong() */
	rc = pthread_create(&t1_pong, &attr, pong, NULL);
	if (rc)
		pr_error(rc, "pthread_create()");

	rc = pthread_join(t0_ping, NULL);
	if (rc)
		pr_error(rc, "pthread_join()");

	rc = pthread_join(t1_pong, NULL);
	if (rc)
		pr_error(rc, "pthread_join()");

	if (success) {
		printf("no.\n"); /* no, endianness did not flip inadvertently */
		return EXIT_SUCCESS;
	}

	printf("yes!\n"); /* yes, endianness did flip inadvertently */
	return EXIT_FAILURE;
}