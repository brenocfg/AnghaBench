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
typedef  int umode_t ;
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IALLUGO ; 
 int /*<<< orphan*/  TOMOYO_TYPE_MKDIR ; 
 int tomoyo_path_number_perm (int /*<<< orphan*/ ,struct path*,int) ; 

__attribute__((used)) static int tomoyo_path_mkdir(const struct path *parent, struct dentry *dentry,
			     umode_t mode)
{
	struct path path = { .mnt = parent->mnt, .dentry = dentry };

	return tomoyo_path_number_perm(TOMOYO_TYPE_MKDIR, &path,
				       mode & S_IALLUGO);
}