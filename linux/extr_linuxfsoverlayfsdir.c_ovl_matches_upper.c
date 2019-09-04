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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ d_inode (struct dentry*) ; 
 struct dentry* ovl_dentry_upper (struct dentry*) ; 

__attribute__((used)) static bool ovl_matches_upper(struct dentry *dentry, struct dentry *upper)
{
	return d_inode(ovl_dentry_upper(dentry)) == d_inode(upper);
}