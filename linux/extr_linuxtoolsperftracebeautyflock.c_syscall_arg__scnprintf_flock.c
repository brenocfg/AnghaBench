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
struct syscall_arg {int val; } ;

/* Variables and functions */
 int LOCK_EX ; 
 int LOCK_MAND ; 
 int LOCK_NB ; 
 int LOCK_READ ; 
 int LOCK_RW ; 
 int LOCK_SH ; 
 int LOCK_UN ; 
 int LOCK_WRITE ; 
 size_t scnprintf (char*,size_t,char*,...) ; 

size_t syscall_arg__scnprintf_flock(char *bf, size_t size, struct syscall_arg *arg)
{
	int printed = 0, op = arg->val;

	if (op == 0)
		return scnprintf(bf, size, "NONE");
#define	P_CMD(cmd) \
	if ((op & LOCK_##cmd) == LOCK_##cmd) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #cmd); \
		op &= ~LOCK_##cmd; \
	}

	P_CMD(SH);
	P_CMD(EX);
	P_CMD(NB);
	P_CMD(UN);
	P_CMD(MAND);
	P_CMD(RW);
	P_CMD(READ);
	P_CMD(WRITE);
#undef P_OP

	if (op)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", op);

	return printed;
}