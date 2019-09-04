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
 int SOCK_CLOEXEC ; 
#define  SOCK_DCCP 134 
#define  SOCK_DGRAM 133 
 int SOCK_NONBLOCK ; 
#define  SOCK_PACKET 132 
#define  SOCK_RAW 131 
#define  SOCK_RDM 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 int SOCK_TYPE_MASK ; 
 size_t scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_socket_type(char *bf, size_t size, struct syscall_arg *arg)
{
	size_t printed;
	int type = arg->val,
	    flags = type & ~SOCK_TYPE_MASK;

	type &= SOCK_TYPE_MASK;
	/*
	 * Can't use a strarray, MIPS may override for ABI reasons.
	 */
	switch (type) {
#define	P_SK_TYPE(n) case SOCK_##n: printed = scnprintf(bf, size, #n); break;
	P_SK_TYPE(STREAM);
	P_SK_TYPE(DGRAM);
	P_SK_TYPE(RAW);
	P_SK_TYPE(RDM);
	P_SK_TYPE(SEQPACKET);
	P_SK_TYPE(DCCP);
	P_SK_TYPE(PACKET);
#undef P_SK_TYPE
	default:
		printed = scnprintf(bf, size, "%#x", type);
	}

#define	P_SK_FLAG(n) \
	if (flags & SOCK_##n) { \
		printed += scnprintf(bf + printed, size - printed, "|%s", #n); \
		flags &= ~SOCK_##n; \
	}

	P_SK_FLAG(CLOEXEC);
	P_SK_FLAG(NONBLOCK);
#undef P_SK_FLAG

	if (flags)
		printed += scnprintf(bf + printed, size - printed, "|%#x", flags);

	return printed;
}