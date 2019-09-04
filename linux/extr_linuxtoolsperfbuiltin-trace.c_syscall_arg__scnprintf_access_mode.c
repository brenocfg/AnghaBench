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
 int F_OK ; 
 int R_OK ; 
 int W_OK ; 
 int X_OK ; 
 size_t scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_access_mode(char *bf, size_t size,
						 struct syscall_arg *arg)
{
	size_t printed = 0;
	int mode = arg->val;

	if (mode == F_OK) /* 0 */
		return scnprintf(bf, size, "F");
#define	P_MODE(n) \
	if (mode & n##_OK) { \
		printed += scnprintf(bf + printed, size - printed, "%s", #n); \
		mode &= ~n##_OK; \
	}

	P_MODE(R);
	P_MODE(W);
	P_MODE(X);
#undef P_MODE

	if (mode)
		printed += scnprintf(bf + printed, size - printed, "|%#x", mode);

	return printed;
}