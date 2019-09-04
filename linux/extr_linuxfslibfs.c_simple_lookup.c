#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct dentry {TYPE_2__* d_sb; TYPE_1__ d_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ NAME_MAX ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_set_d_op (struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_dentry_operations ; 

struct dentry *simple_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
{
	if (dentry->d_name.len > NAME_MAX)
		return ERR_PTR(-ENAMETOOLONG);
	if (!dentry->d_sb->s_d_op)
		d_set_d_op(dentry, &simple_dentry_operations);
	d_add(dentry, NULL);
	return NULL;
}