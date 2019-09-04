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
 int WCONTINUED ; 
 int WNOHANG ; 
 int WUNTRACED ; 
 scalar_t__ scnprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_waitid_options(char *bf, size_t size,
						    struct syscall_arg *arg)
{
	int printed = 0, options = arg->val;

#define	P_OPTION(n) \
	if (options & W##n) { \
		printed += scnprintf(bf + printed, size - printed, "%s%s", printed ? "|" : "", #n); \
		options &= ~W##n; \
	}

	P_OPTION(NOHANG);
	P_OPTION(UNTRACED);
	P_OPTION(CONTINUED);
#undef P_OPTION

	if (options)
		printed += scnprintf(bf + printed, size - printed, "%s%#x", printed ? "|" : "", options);

	return printed;
}