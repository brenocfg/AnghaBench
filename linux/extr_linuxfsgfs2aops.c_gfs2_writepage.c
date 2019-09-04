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
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_get_block_noalloc ; 
 int gfs2_writepage_common (struct page*,struct writeback_control*) ; 
 int nobh_writepage (struct page*,int /*<<< orphan*/ ,struct writeback_control*) ; 

__attribute__((used)) static int gfs2_writepage(struct page *page, struct writeback_control *wbc)
{
	int ret;

	ret = gfs2_writepage_common(page, wbc);
	if (ret <= 0)
		return ret;

	return nobh_writepage(page, gfs2_get_block_noalloc, wbc);
}