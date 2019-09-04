#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct TYPE_2__ {unsigned long tv_usec; } ;
struct itimerval {TYPE_1__ it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  memset (struct itimerval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigalrm_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ soak_done ; 

__attribute__((used)) static void cpu_soak_usecs(unsigned long usecs)
{
	struct itimerval val;

	memset(&val, 0, sizeof(val));
	val.it_value.tv_usec = usecs;

	signal(SIGALRM, sigalrm_handler);
	setitimer(ITIMER_REAL, &val, NULL);

	while (1) {
		if (soak_done)
			break;
	}

	signal(SIGALRM, SIG_DFL);
}