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
struct TYPE_2__ {int /*<<< orphan*/  i_data; } ;
struct udf_inode_info {TYPE_1__ i_ext; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  kmalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udf_alloc_i_data(struct inode *inode, size_t size)
{
	struct udf_inode_info *iinfo = UDF_I(inode);
	iinfo->i_ext.i_data = kmalloc(size, GFP_KERNEL);
	if (!iinfo->i_ext.i_data)
		return -ENOMEM;
	return 0;
}