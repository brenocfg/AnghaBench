#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; } ;
struct hfs_iget_data {TYPE_3__* rec; } ;
struct TYPE_5__ {int /*<<< orphan*/  FlNum; } ;
struct TYPE_4__ {int /*<<< orphan*/  DirID; } ;
struct TYPE_6__ {int type; TYPE_2__ file; TYPE_1__ dir; } ;
typedef  TYPE_3__ hfs_cat_rec ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  HFS_CDR_DIR 129 
#define  HFS_CDR_FIL 128 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hfs_test_inode(struct inode *inode, void *data)
{
	struct hfs_iget_data *idata = data;
	hfs_cat_rec *rec;

	rec = idata->rec;
	switch (rec->type) {
	case HFS_CDR_DIR:
		return inode->i_ino == be32_to_cpu(rec->dir.DirID);
	case HFS_CDR_FIL:
		return inode->i_ino == be32_to_cpu(rec->file.FlNum);
	default:
		BUG();
		return 1;
	}
}