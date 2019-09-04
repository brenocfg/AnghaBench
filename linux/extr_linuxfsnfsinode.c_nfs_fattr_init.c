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
struct nfs_fattr {int /*<<< orphan*/ * group_name; int /*<<< orphan*/ * owner_name; int /*<<< orphan*/  gencount; int /*<<< orphan*/  time_start; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nfs_inc_attr_generation_counter () ; 

void nfs_fattr_init(struct nfs_fattr *fattr)
{
	fattr->valid = 0;
	fattr->time_start = jiffies;
	fattr->gencount = nfs_inc_attr_generation_counter();
	fattr->owner_name = NULL;
	fattr->group_name = NULL;
}