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
struct syscall_arg {int val; int mask; } ;

/* Variables and functions */
 int FUTEX_CLOCK_REALTIME ; 
 int FUTEX_CMD_MASK ; 
#define  FUTEX_CMP_REQUEUE 140 
#define  FUTEX_CMP_REQUEUE_PI 139 
#define  FUTEX_FD 138 
#define  FUTEX_LOCK_PI 137 
 int FUTEX_PRIVATE_FLAG ; 
#define  FUTEX_REQUEUE 136 
#define  FUTEX_TRYLOCK_PI 135 
#define  FUTEX_UNLOCK_PI 134 
#define  FUTEX_WAIT 133 
#define  FUTEX_WAIT_BITSET 132 
#define  FUTEX_WAIT_REQUEUE_PI 131 
#define  FUTEX_WAKE 130 
#define  FUTEX_WAKE_BITSET 129 
#define  FUTEX_WAKE_OP 128 
 size_t scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_futex_op(char *bf, size_t size, struct syscall_arg *arg)
{
	enum syscall_futex_args {
		SCF_UADDR   = (1 << 0),
		SCF_OP	    = (1 << 1),
		SCF_VAL	    = (1 << 2),
		SCF_TIMEOUT = (1 << 3),
		SCF_UADDR2  = (1 << 4),
		SCF_VAL3    = (1 << 5),
	};
	int op = arg->val;
	int cmd = op & FUTEX_CMD_MASK;
	size_t printed = 0;

	switch (cmd) {
#define	P_FUTEX_OP(n) case FUTEX_##n: printed = scnprintf(bf, size, #n);
	P_FUTEX_OP(WAIT);	    arg->mask |= SCF_VAL3|SCF_UADDR2;		  break;
	P_FUTEX_OP(WAKE);	    arg->mask |= SCF_VAL3|SCF_UADDR2|SCF_TIMEOUT; break;
	P_FUTEX_OP(FD);		    arg->mask |= SCF_VAL3|SCF_UADDR2|SCF_TIMEOUT; break;
	P_FUTEX_OP(REQUEUE);	    arg->mask |= SCF_VAL3|SCF_TIMEOUT;	          break;
	P_FUTEX_OP(CMP_REQUEUE);    arg->mask |= SCF_TIMEOUT;			  break;
	P_FUTEX_OP(CMP_REQUEUE_PI); arg->mask |= SCF_TIMEOUT;			  break;
	P_FUTEX_OP(WAKE_OP);							  break;
	P_FUTEX_OP(LOCK_PI);	    arg->mask |= SCF_VAL3|SCF_UADDR2|SCF_TIMEOUT; break;
	P_FUTEX_OP(UNLOCK_PI);	    arg->mask |= SCF_VAL3|SCF_UADDR2|SCF_TIMEOUT; break;
	P_FUTEX_OP(TRYLOCK_PI);	    arg->mask |= SCF_VAL3|SCF_UADDR2;		  break;
	P_FUTEX_OP(WAIT_BITSET);    arg->mask |= SCF_UADDR2;			  break;
	P_FUTEX_OP(WAKE_BITSET);    arg->mask |= SCF_UADDR2;			  break;
	P_FUTEX_OP(WAIT_REQUEUE_PI);						  break;
	default: printed = scnprintf(bf, size, "%#x", cmd);			  break;
	}

	if (op & FUTEX_PRIVATE_FLAG)
		printed += scnprintf(bf + printed, size - printed, "|PRIV");

	if (op & FUTEX_CLOCK_REALTIME)
		printed += scnprintf(bf + printed, size - printed, "|CLKRT");

	return printed;
}