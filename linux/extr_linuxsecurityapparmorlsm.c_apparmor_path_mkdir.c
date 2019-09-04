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
typedef  int /*<<< orphan*/  umode_t ;
struct path {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_MAY_CREATE ; 
 int /*<<< orphan*/  OP_MKDIR ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int common_perm_create (int /*<<< orphan*/ ,struct path const*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apparmor_path_mkdir(const struct path *dir, struct dentry *dentry,
			       umode_t mode)
{
	return common_perm_create(OP_MKDIR, dir, dentry, AA_MAY_CREATE,
				  S_IFDIR);
}