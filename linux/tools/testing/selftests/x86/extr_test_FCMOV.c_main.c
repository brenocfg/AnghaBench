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

/* Variables and functions */
 int /*<<< orphan*/  CF ; 
 int /*<<< orphan*/  PF ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  ZF ; 
 double fcmovb (int /*<<< orphan*/ ) ; 
 double fcmovbe (int /*<<< orphan*/ ) ; 
 double fcmove (int /*<<< orphan*/ ) ; 
 double fcmovnb (int /*<<< orphan*/ ) ; 
 double fcmovnbe (int /*<<< orphan*/ ) ; 
 double fcmovne (int /*<<< orphan*/ ) ; 
 double fcmovnu (int /*<<< orphan*/ ) ; 
 double fcmovu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sighandler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv, char **envp)
{
	int err = 0;

	/* SIGILL triggers on 32-bit kernels w/o fcomi emulation
	 * when run with "no387 nofxsr". Other signals are caught
	 * just in case.
	 */
	signal(SIGILL, sighandler);
	signal(SIGFPE, sighandler);
	signal(SIGSEGV, sighandler);

	printf("[RUN]\tTesting fcmovCC instructions\n");
	/* If fcmovCC() returns 1.0, the move wasn't done */
	err |= !(fcmovb(0)   == 1.0); err |= !(fcmovnb(0)  != 1.0);
	err |= !(fcmove(0)   == 1.0); err |= !(fcmovne(0)  != 1.0);
	err |= !(fcmovbe(0)  == 1.0); err |= !(fcmovnbe(0) != 1.0);
	err |= !(fcmovu(0)   == 1.0); err |= !(fcmovnu(0)  != 1.0);

	err |= !(fcmovb(CF)  != 1.0); err |= !(fcmovnb(CF)  == 1.0);
	err |= !(fcmove(CF)  == 1.0); err |= !(fcmovne(CF)  != 1.0);
	err |= !(fcmovbe(CF) != 1.0); err |= !(fcmovnbe(CF) == 1.0);
	err |= !(fcmovu(CF)  == 1.0); err |= !(fcmovnu(CF)  != 1.0);

	err |= !(fcmovb(ZF)  == 1.0); err |= !(fcmovnb(ZF)  != 1.0);
	err |= !(fcmove(ZF)  != 1.0); err |= !(fcmovne(ZF)  == 1.0);
	err |= !(fcmovbe(ZF) != 1.0); err |= !(fcmovnbe(ZF) == 1.0);
	err |= !(fcmovu(ZF)  == 1.0); err |= !(fcmovnu(ZF)  != 1.0);

	err |= !(fcmovb(PF)  == 1.0); err |= !(fcmovnb(PF)  != 1.0);
	err |= !(fcmove(PF)  == 1.0); err |= !(fcmovne(PF)  != 1.0);
	err |= !(fcmovbe(PF) == 1.0); err |= !(fcmovnbe(PF) != 1.0);
	err |= !(fcmovu(PF)  != 1.0); err |= !(fcmovnu(PF)  == 1.0);

        if (!err)
                printf("[OK]\tfcmovCC\n");
	else
		printf("[FAIL]\tfcmovCC errors: %d\n", err);

	return err;
}