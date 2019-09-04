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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vfree_deferred (void const*) ; 
 int /*<<< orphan*/  __vunmap (void const*,int) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  in_nmi () ; 
 int /*<<< orphan*/  kmemleak_free (void const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void vfree(const void *addr)
{
	BUG_ON(in_nmi());

	kmemleak_free(addr);

	if (!addr)
		return;
	if (unlikely(in_interrupt()))
		__vfree_deferred(addr);
	else
		__vunmap(addr, 1);
}