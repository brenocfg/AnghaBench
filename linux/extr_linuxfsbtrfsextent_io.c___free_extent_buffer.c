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
struct extent_buffer {int /*<<< orphan*/  leak_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_leak_debug_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_buffer_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct extent_buffer*) ; 

__attribute__((used)) static void __free_extent_buffer(struct extent_buffer *eb)
{
	btrfs_leak_debug_del(&eb->leak_list);
	kmem_cache_free(extent_buffer_cache, eb);
}