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
 int CF ; 
 int PF ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int ZF ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sighandler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test (int) ; 
 int test_qnan (int) ; 
 int testp (int) ; 
 int testp_qnan (int) ; 
 int testu_qnan (int) ; 
 int testu_snan (int) ; 
 int testup_qnan (int) ; 

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

	printf("[RUN]\tTesting f[u]comi[p] instructions\n");
	err |= test(0);
	err |= test_qnan(0);
	err |= testu_qnan(0);
	err |= testu_snan(0);
	err |= test(CF|ZF|PF);
	err |= test_qnan(CF|ZF|PF);
	err |= testu_qnan(CF|ZF|PF);
	err |= testu_snan(CF|ZF|PF);
	err |= testp(0);
	err |= testp_qnan(0);
	err |= testup_qnan(0);
	err |= testp(CF|ZF|PF);
	err |= testp_qnan(CF|ZF|PF);
	err |= testup_qnan(CF|ZF|PF);
	if (!err)
		printf("[OK]\tf[u]comi[p]\n");
	else
		printf("[FAIL]\tf[u]comi[p] errors: %d\n", err);

	return err;
}