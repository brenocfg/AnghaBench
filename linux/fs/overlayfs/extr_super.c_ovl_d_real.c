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
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {char* s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,struct dentry*,char*,int /*<<< orphan*/ ) ; 
 struct inode const* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_is_reg (struct dentry*) ; 
 struct dentry* d_real (struct dentry*,struct inode const*) ; 
 struct dentry* ovl_dentry_lowerdata (struct dentry*) ; 
 struct dentry* ovl_dentry_upper (struct dentry*) ; 
 scalar_t__ ovl_has_upperdata (struct inode const*) ; 

__attribute__((used)) static struct dentry *ovl_d_real(struct dentry *dentry,
				 const struct inode *inode)
{
	struct dentry *real;

	/* It's an overlay file */
	if (inode && d_inode(dentry) == inode)
		return dentry;

	if (!d_is_reg(dentry)) {
		if (!inode || inode == d_inode(dentry))
			return dentry;
		goto bug;
	}

	real = ovl_dentry_upper(dentry);
	if (real && (inode == d_inode(real)))
		return real;

	if (real && !inode && ovl_has_upperdata(d_inode(dentry)))
		return real;

	real = ovl_dentry_lowerdata(dentry);
	if (!real)
		goto bug;

	/* Handle recursion */
	real = d_real(real, inode);

	if (!inode || inode == d_inode(real))
		return real;
bug:
	WARN(1, "ovl_d_real(%pd4, %s:%lu): real dentry not found\n", dentry,
	     inode ? inode->i_sb->s_id : "NULL", inode ? inode->i_ino : 0);
	return dentry;
}