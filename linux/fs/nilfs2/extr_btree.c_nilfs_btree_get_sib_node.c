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
struct nilfs_btree_path {TYPE_1__* bp_sib_bh; } ;
struct nilfs_btree_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */

__attribute__((used)) static struct nilfs_btree_node *
nilfs_btree_get_sib_node(const struct nilfs_btree_path *path, int level)
{
	return (struct nilfs_btree_node *)path[level].bp_sib_bh->b_data;
}