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
struct super_block {int dummy; } ;
struct ext4_super_block {int /*<<< orphan*/  s_checksum; } ;
struct TYPE_2__ {struct ext4_super_block* s_es; } ;

/* Variables and functions */
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext4_has_metadata_csum (struct super_block*) ; 
 int /*<<< orphan*/  ext4_superblock_csum (struct super_block*,struct ext4_super_block*) ; 

void ext4_superblock_csum_set(struct super_block *sb)
{
	struct ext4_super_block *es = EXT4_SB(sb)->s_es;

	if (!ext4_has_metadata_csum(sb))
		return;

	es->s_checksum = ext4_superblock_csum(sb, es);
}