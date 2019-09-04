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
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static inline bool arch_syscall_match_sym_name(const char *sym, const char *name)
{
	/*
	 * Only compare after the "sys" prefix. Archs that use
	 * syscall wrappers may have syscalls symbols aliases prefixed
	 * with ".SyS" or ".sys" instead of "sys", leading to an unwanted
	 * mismatch.
	 */
	return !strcmp(sym + 3, name + 3);
}