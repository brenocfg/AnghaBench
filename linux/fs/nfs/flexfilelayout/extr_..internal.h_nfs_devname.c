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
 int /*<<< orphan*/  NFS_PATH_CANONICAL ; 
 char* nfs_path (char**,struct dentry*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *nfs_devname(struct dentry *dentry,
				char *buffer, ssize_t buflen)
{
	char *dummy;
	return nfs_path(&dummy, dentry, buffer, buflen, NFS_PATH_CANONICAL);
}