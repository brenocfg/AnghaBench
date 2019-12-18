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
typedef  int /*<<< orphan*/  u32 ;
struct extent_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_item_nr (int) ; 
 int /*<<< orphan*/  btrfs_item_offset (struct extent_buffer const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 btrfs_item_offset_nr(const struct extent_buffer *eb, int nr)
{
	return btrfs_item_offset(eb, btrfs_item_nr(nr));
}