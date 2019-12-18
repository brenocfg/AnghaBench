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
struct path {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_MAY_DELETE ; 
 int /*<<< orphan*/  OP_RMDIR ; 
 int common_perm_rm (int /*<<< orphan*/ ,struct path const*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apparmor_path_rmdir(const struct path *dir, struct dentry *dentry)
{
	return common_perm_rm(OP_RMDIR, dir, dentry, AA_MAY_DELETE);
}