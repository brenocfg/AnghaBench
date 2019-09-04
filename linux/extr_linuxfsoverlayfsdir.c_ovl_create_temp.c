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
struct ovl_cattr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* ovl_create_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ovl_cattr*) ; 
 int /*<<< orphan*/  ovl_lookup_temp (struct dentry*) ; 

struct dentry *ovl_create_temp(struct dentry *workdir, struct ovl_cattr *attr)
{
	return ovl_create_real(d_inode(workdir), ovl_lookup_temp(workdir),
			       attr);
}