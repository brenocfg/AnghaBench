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
struct inode {int dummy; } ;
struct address_space {int /*<<< orphan*/ * a_ops; int /*<<< orphan*/ * private_data; scalar_t__ flags; struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  empty_aops ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (struct address_space*,int /*<<< orphan*/ ) ; 

void nilfs_mapping_init(struct address_space *mapping, struct inode *inode)
{
	mapping->host = inode;
	mapping->flags = 0;
	mapping_set_gfp_mask(mapping, GFP_NOFS);
	mapping->private_data = NULL;
	mapping->a_ops = &empty_aops;
}