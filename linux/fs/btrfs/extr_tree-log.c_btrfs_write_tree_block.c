#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct extent_buffer {scalar_t__ len; scalar_t__ start; TYPE_1__** pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int filemap_fdatawrite_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int btrfs_write_tree_block(struct extent_buffer *buf)
{
	return filemap_fdatawrite_range(buf->pages[0]->mapping, buf->start,
					buf->start + buf->len - 1);
}