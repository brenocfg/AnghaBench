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
struct path {TYPE_1__* dentry; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILESYSTEM__REMOUNT ; 
 int /*<<< orphan*/  FILE__MOUNTON ; 
 unsigned long MS_REMOUNT ; 
 struct cred* current_cred () ; 
 int path_has_perm (struct cred const*,struct path const*,int /*<<< orphan*/ ) ; 
 int superblock_has_perm (struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int selinux_mount(const char *dev_name,
			 const struct path *path,
			 const char *type,
			 unsigned long flags,
			 void *data)
{
	const struct cred *cred = current_cred();

	if (flags & MS_REMOUNT)
		return superblock_has_perm(cred, path->dentry->d_sb,
					   FILESYSTEM__REMOUNT, NULL);
	else
		return path_has_perm(cred, path, FILE__MOUNTON);
}