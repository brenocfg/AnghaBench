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
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  truncate_lock; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fat_get_block_bmap ; 
 int /*<<< orphan*/  generic_block_bmap (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sector_t _fat_bmap(struct address_space *mapping, sector_t block)
{
	sector_t blocknr;

	/* fat_get_cluster() assumes the requested blocknr isn't truncated. */
	down_read(&MSDOS_I(mapping->host)->truncate_lock);
	blocknr = generic_block_bmap(mapping, block, fat_get_block_bmap);
	up_read(&MSDOS_I(mapping->host)->truncate_lock);

	return blocknr;
}