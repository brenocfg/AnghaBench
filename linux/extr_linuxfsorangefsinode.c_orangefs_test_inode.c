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
struct orangefs_object_kref {scalar_t__ fs_id; int /*<<< orphan*/  khandle; } ;
struct TYPE_2__ {scalar_t__ fs_id; int /*<<< orphan*/  khandle; } ;
struct orangefs_inode_s {TYPE_1__ refn; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct orangefs_inode_s* ORANGEFS_I (struct inode*) ; 
 int /*<<< orphan*/  ORANGEFS_khandle_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int orangefs_test_inode(struct inode *inode, void *data)
{
	struct orangefs_object_kref *ref = (struct orangefs_object_kref *) data;
	struct orangefs_inode_s *orangefs_inode = NULL;

	orangefs_inode = ORANGEFS_I(inode);
	/* test handles and fs_ids... */
	return (!ORANGEFS_khandle_cmp(&(orangefs_inode->refn.khandle),
				&(ref->khandle)) &&
			orangefs_inode->refn.fs_id == ref->fs_id);
}