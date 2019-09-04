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
struct page {int dummy; } ;

/* Variables and functions */

void noop_invalidatepage(struct page *page, unsigned int offset,
		unsigned int length)
{
	/*
	 * There is no page cache to invalidate in the dax case, however
	 * we need this callback defined to prevent falling back to
	 * block_invalidatepage() in do_invalidatepage().
	 */
}