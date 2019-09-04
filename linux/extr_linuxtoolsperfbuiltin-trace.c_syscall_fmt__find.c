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
struct syscall_fmt {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct syscall_fmt* bsearch (char const*,int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall_fmt__cmp ; 
 int /*<<< orphan*/  syscall_fmts ; 

__attribute__((used)) static struct syscall_fmt *syscall_fmt__find(const char *name)
{
	const int nmemb = ARRAY_SIZE(syscall_fmts);
	return bsearch(name, syscall_fmts, nmemb, sizeof(struct syscall_fmt), syscall_fmt__cmp);
}