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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_info_struct {struct block_device* bdev; } ;
struct swap_extent {scalar_t__ start_page; scalar_t__ start_block; } ;
struct block_device {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 struct swap_extent* offset_to_swap_extent (struct swap_info_struct*,scalar_t__) ; 
 scalar_t__ swp_offset (int /*<<< orphan*/ ) ; 
 struct swap_info_struct* swp_swap_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sector_t map_swap_entry(swp_entry_t entry, struct block_device **bdev)
{
	struct swap_info_struct *sis;
	struct swap_extent *se;
	pgoff_t offset;

	sis = swp_swap_info(entry);
	*bdev = sis->bdev;

	offset = swp_offset(entry);
	se = offset_to_swap_extent(sis, offset);
	return se->start_block + (offset - se->start_page);
}