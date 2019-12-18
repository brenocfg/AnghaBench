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
struct extent_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_release_extent_buffer_pages (struct extent_buffer*) ; 

__attribute__((used)) static inline void btrfs_release_extent_buffer(struct extent_buffer *eb)
{
	btrfs_release_extent_buffer_pages(eb);
	__free_extent_buffer(eb);
}