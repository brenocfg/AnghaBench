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
typedef  int /*<<< orphan*/  u32 ;
struct path_cond {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct path {int /*<<< orphan*/  dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int common_perm (char const*,struct path const*,int /*<<< orphan*/ ,struct path_cond*) ; 
 TYPE_1__* d_backing_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_mediated_fs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int common_perm_cond(const char *op, const struct path *path, u32 mask)
{
	struct path_cond cond = { d_backing_inode(path->dentry)->i_uid,
				  d_backing_inode(path->dentry)->i_mode
	};

	if (!path_mediated_fs(path->dentry))
		return 0;

	return common_perm(op, path, mask, &cond);
}