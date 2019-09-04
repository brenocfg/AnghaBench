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
struct quad_buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  sb_dmap; } ;

/* Variables and functions */
 int /*<<< orphan*/ * hpfs_map_4sectors (struct super_block*,int /*<<< orphan*/ ,struct quad_buffer_head*,int /*<<< orphan*/ ) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 

__le32 *hpfs_map_dnode_bitmap(struct super_block *s, struct quad_buffer_head *qbh)
{
	return hpfs_map_4sectors(s, hpfs_sb(s)->sb_dmap, qbh, 0);
}