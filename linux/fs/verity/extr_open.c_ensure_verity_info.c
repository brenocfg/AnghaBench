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
struct inode {TYPE_2__* i_sb; } ;
struct fsverity_info {int dummy; } ;
struct fsverity_descriptor {int dummy; } ;
struct TYPE_4__ {TYPE_1__* s_vop; } ;
struct TYPE_3__ {int (* get_verity_descriptor ) (struct inode*,struct fsverity_descriptor*,int) ;} ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int FS_VERITY_MAX_DESCRIPTOR_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct fsverity_info*) ; 
 int PTR_ERR (struct fsverity_info*) ; 
 struct fsverity_info* fsverity_create_info (struct inode*,struct fsverity_descriptor*,int) ; 
 int /*<<< orphan*/  fsverity_err (struct inode*,char*,int) ; 
 struct fsverity_info* fsverity_get_info (struct inode*) ; 
 int /*<<< orphan*/  fsverity_set_info (struct inode*,struct fsverity_info*) ; 
 int /*<<< orphan*/  kfree (struct fsverity_descriptor*) ; 
 struct fsverity_descriptor* kmalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,struct fsverity_descriptor*,int) ; 
 int stub2 (struct inode*,struct fsverity_descriptor*,int) ; 

__attribute__((used)) static int ensure_verity_info(struct inode *inode)
{
	struct fsverity_info *vi = fsverity_get_info(inode);
	struct fsverity_descriptor *desc;
	int res;

	if (vi)
		return 0;

	res = inode->i_sb->s_vop->get_verity_descriptor(inode, NULL, 0);
	if (res < 0) {
		fsverity_err(inode,
			     "Error %d getting verity descriptor size", res);
		return res;
	}
	if (res > FS_VERITY_MAX_DESCRIPTOR_SIZE) {
		fsverity_err(inode, "Verity descriptor is too large (%d bytes)",
			     res);
		return -EMSGSIZE;
	}
	desc = kmalloc(res, GFP_KERNEL);
	if (!desc)
		return -ENOMEM;
	res = inode->i_sb->s_vop->get_verity_descriptor(inode, desc, res);
	if (res < 0) {
		fsverity_err(inode, "Error %d reading verity descriptor", res);
		goto out_free_desc;
	}

	vi = fsverity_create_info(inode, desc, res);
	if (IS_ERR(vi)) {
		res = PTR_ERR(vi);
		goto out_free_desc;
	}

	fsverity_set_info(inode, vi);
	res = 0;
out_free_desc:
	kfree(desc);
	return res;
}