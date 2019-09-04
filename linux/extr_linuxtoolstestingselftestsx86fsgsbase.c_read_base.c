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
typedef  enum which_base { ____Placeholder_which_base } which_base ;

/* Variables and functions */
 int FS ; 
 int ULONG_MAX ; 
 int /*<<< orphan*/  abort () ; 
 unsigned long segv_addr ; 
 int want_segv ; 

__attribute__((used)) static unsigned long read_base(enum which_base which)
{
	unsigned long offset;
	/*
	 * Unless we have FSGSBASE, there's no direct way to do this from
	 * user mode.  We can get at it indirectly using signals, though.
	 */

	want_segv = true;

	offset = 0;
	if (which == FS) {
		/* Use a constant-length instruction here. */
		asm volatile ("mov %%fs:(%%rcx), %%rax" : : "c" (offset) : "rax");
	} else {
		asm volatile ("mov %%gs:(%%rcx), %%rax" : : "c" (offset) : "rax");
	}
	if (!want_segv)
		return segv_addr + offset;

	/*
	 * If that didn't segfault, try the other end of the address space.
	 * Unless we get really unlucky and run into the vsyscall page, this
	 * is guaranteed to segfault.
	 */

	offset = (ULONG_MAX >> 1) + 1;
	if (which == FS) {
		asm volatile ("mov %%fs:(%%rcx), %%rax"
			      : : "c" (offset) : "rax");
	} else {
		asm volatile ("mov %%gs:(%%rcx), %%rax"
			      : : "c" (offset) : "rax");
	}
	if (!want_segv)
		return segv_addr + offset;

	abort();
}