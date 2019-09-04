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
struct adfs_sb_info {int s_map_size; TYPE_1__* s_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  dm_bh; } ;

/* Variables and functions */
 struct adfs_sb_info* ADFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree_rcu (struct adfs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void adfs_put_super(struct super_block *sb)
{
	int i;
	struct adfs_sb_info *asb = ADFS_SB(sb);

	for (i = 0; i < asb->s_map_size; i++)
		brelse(asb->s_map[i].dm_bh);
	kfree(asb->s_map);
	kfree_rcu(asb, rcu);
}