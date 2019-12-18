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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (char*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 char* dentry_path_raw (struct dentry*,char* const,int const) ; 

__attribute__((used)) static char *tomoyo_get_dentry_path(struct dentry *dentry, char * const buffer,
				    const int buflen)
{
	char *pos = ERR_PTR(-ENOMEM);

	if (buflen >= 256) {
		pos = dentry_path_raw(dentry, buffer, buflen - 1);
		if (!IS_ERR(pos) && *pos == '/' && pos[1]) {
			struct inode *inode = d_backing_inode(dentry);

			if (inode && S_ISDIR(inode->i_mode)) {
				buffer[buflen - 2] = '/';
				buffer[buflen - 1] = '\0';
			}
		}
	}
	return pos;
}