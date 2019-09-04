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
struct path {TYPE_2__* dentry; } ;
struct aa_profile {int path_flags; } ;
struct TYPE_4__ {TYPE_1__* d_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int PATH_IS_DIR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int path_flags(struct aa_profile *profile, const struct path *path)
{
	AA_BUG(!profile);
	AA_BUG(!path);

	return profile->path_flags |
		(S_ISDIR(path->dentry->d_inode->i_mode) ? PATH_IS_DIR : 0);
}