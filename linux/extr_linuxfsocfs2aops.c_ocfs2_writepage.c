#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct TYPE_4__ {scalar_t__ ip_blkno; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_2__* OCFS2_I (int /*<<< orphan*/ ) ; 
 int block_write_full_page (struct page*,int /*<<< orphan*/ ,struct writeback_control*) ; 
 int /*<<< orphan*/  ocfs2_get_block ; 
 int /*<<< orphan*/  trace_ocfs2_writepage (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_writepage(struct page *page, struct writeback_control *wbc)
{
	trace_ocfs2_writepage(
		(unsigned long long)OCFS2_I(page->mapping->host)->ip_blkno,
		page->index);

	return block_write_full_page(page, ocfs2_get_block, wbc);
}