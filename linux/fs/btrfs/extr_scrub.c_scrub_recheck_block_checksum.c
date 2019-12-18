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
struct scrub_block {TYPE_1__** pagev; scalar_t__ generation_error; scalar_t__ checksum_error; scalar_t__ header_error; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int BTRFS_EXTENT_FLAG_DATA ; 
 int /*<<< orphan*/  scrub_checksum_data (struct scrub_block*) ; 
 int /*<<< orphan*/  scrub_checksum_tree_block (struct scrub_block*) ; 

__attribute__((used)) static void scrub_recheck_block_checksum(struct scrub_block *sblock)
{
	sblock->header_error = 0;
	sblock->checksum_error = 0;
	sblock->generation_error = 0;

	if (sblock->pagev[0]->flags & BTRFS_EXTENT_FLAG_DATA)
		scrub_checksum_data(sblock);
	else
		scrub_checksum_tree_block(sblock);
}