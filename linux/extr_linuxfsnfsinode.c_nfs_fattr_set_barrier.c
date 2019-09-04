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
struct nfs_fattr {int /*<<< orphan*/  gencount; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_inc_attr_generation_counter () ; 

void nfs_fattr_set_barrier(struct nfs_fattr *fattr)
{
	fattr->gencount = nfs_inc_attr_generation_counter();
}