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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (char*) ; 
 int /*<<< orphan*/  NFS_PATH_CANONICAL ; 
 char* nfs_path (char**,struct dentry*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nfs_path_component (char*,char*) ; 

__attribute__((used)) static char *nfs4_path(struct dentry *dentry, char *buffer, ssize_t buflen)
{
	char *limit;
	char *path = nfs_path(&limit, dentry, buffer, buflen,
			      NFS_PATH_CANONICAL);
	if (!IS_ERR(path)) {
		char *path_component = nfs_path_component(path, limit);
		if (path_component)
			return path_component;
	}
	return path;
}