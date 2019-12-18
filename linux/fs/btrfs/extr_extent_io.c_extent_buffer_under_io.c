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
struct extent_buffer {int /*<<< orphan*/  bflags; int /*<<< orphan*/  io_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_BUFFER_DIRTY ; 
 int /*<<< orphan*/  EXTENT_BUFFER_WRITEBACK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int extent_buffer_under_io(struct extent_buffer *eb)
{
	return (atomic_read(&eb->io_pages) ||
		test_bit(EXTENT_BUFFER_WRITEBACK, &eb->bflags) ||
		test_bit(EXTENT_BUFFER_DIRTY, &eb->bflags));
}