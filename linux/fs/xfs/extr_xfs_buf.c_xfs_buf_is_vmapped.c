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
struct xfs_buf {int b_page_count; scalar_t__ b_addr; } ;

/* Variables and functions */

__attribute__((used)) static inline int
xfs_buf_is_vmapped(
	struct xfs_buf	*bp)
{
	/*
	 * Return true if the buffer is vmapped.
	 *
	 * b_addr is null if the buffer is not mapped, but the code is clever
	 * enough to know it doesn't have to map a single page, so the check has
	 * to be both for b_addr and bp->b_page_count > 1.
	 */
	return bp->b_addr && bp->b_page_count > 1;
}