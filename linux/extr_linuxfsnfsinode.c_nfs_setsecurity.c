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
struct nfs_fattr {int dummy; } ;
struct nfs4_label {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */

void nfs_setsecurity(struct inode *inode, struct nfs_fattr *fattr,
					struct nfs4_label *label)
{
}