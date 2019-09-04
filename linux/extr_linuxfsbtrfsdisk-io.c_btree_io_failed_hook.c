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
struct page {scalar_t__ private; } ;
struct extent_buffer {int read_mirror; int /*<<< orphan*/  bflags; int /*<<< orphan*/  io_pages; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXTENT_BUFFER_READAHEAD ; 
 int /*<<< orphan*/  EXTENT_BUFFER_READ_ERR ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_readahead_hook (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btree_io_failed_hook(struct page *page, int failed_mirror)
{
	struct extent_buffer *eb;

	eb = (struct extent_buffer *)page->private;
	set_bit(EXTENT_BUFFER_READ_ERR, &eb->bflags);
	eb->read_mirror = failed_mirror;
	atomic_dec(&eb->io_pages);
	if (test_and_clear_bit(EXTENT_BUFFER_READAHEAD, &eb->bflags))
		btree_readahead_hook(eb, -EIO);
	return -EIO;	/* we fixed nothing */
}