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
struct syscall_fmt {scalar_t__ alias; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct syscall_fmt*) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 
 struct syscall_fmt* syscall_fmts ; 

__attribute__((used)) static struct syscall_fmt *syscall_fmt__find_by_alias(const char *alias)
{
	int i, nmemb = ARRAY_SIZE(syscall_fmts);

	for (i = 0; i < nmemb; ++i) {
		if (syscall_fmts[i].alias && strcmp(syscall_fmts[i].alias, alias) == 0)
			return &syscall_fmts[i];
	}

	return NULL;
}