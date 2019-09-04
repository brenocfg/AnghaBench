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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  block_invalidatepage (struct page*,unsigned int,unsigned int) ; 
 scalar_t__ buffer_jbd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_buffers (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  trace_ext4_invalidatepage (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static void ext4_invalidatepage(struct page *page, unsigned int offset,
				unsigned int length)
{
	trace_ext4_invalidatepage(page, offset, length);

	/* No journalling happens on data buffers when this function is used */
	WARN_ON(page_has_buffers(page) && buffer_jbd(page_buffers(page)));

	block_invalidatepage(page, offset, length);
}