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
typedef  int /*<<< orphan*/  vattr ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; } ;
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;
struct coda_vattr {int /*<<< orphan*/  va_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_VNON ; 
 int /*<<< orphan*/  coda_cache_clear_inode (struct inode*) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 int /*<<< orphan*/  coda_iattr_to_vattr (struct iattr*,struct coda_vattr*) ; 
 int /*<<< orphan*/  coda_vattr_to_iattr (struct inode*,struct coda_vattr*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  memset (struct coda_vattr*,int /*<<< orphan*/ ,int) ; 
 int venus_setattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct coda_vattr*) ; 

int coda_setattr(struct dentry *de, struct iattr *iattr)
{
	struct inode *inode = d_inode(de);
	struct coda_vattr vattr;
	int error;

	memset(&vattr, 0, sizeof(vattr)); 

	inode->i_ctime = current_time(inode);
	coda_iattr_to_vattr(iattr, &vattr);
	vattr.va_type = C_VNON; /* cannot set type */

	/* Venus is responsible for truncating the container-file!!! */
	error = venus_setattr(inode->i_sb, coda_i2f(inode), &vattr);

	if (!error) {
	        coda_vattr_to_iattr(inode, &vattr); 
		coda_cache_clear_inode(inode);
	}
	return error;
}