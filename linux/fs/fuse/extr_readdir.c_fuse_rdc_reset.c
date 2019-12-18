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
struct inode {int dummy; } ;
struct TYPE_2__ {int cached; scalar_t__ pos; scalar_t__ size; int /*<<< orphan*/  version; } ;
struct fuse_inode {TYPE_1__ rdc; } ;

/* Variables and functions */
 struct fuse_inode* get_fuse_inode (struct inode*) ; 

__attribute__((used)) static void fuse_rdc_reset(struct inode *inode)
{
	struct fuse_inode *fi = get_fuse_inode(inode);

	fi->rdc.cached = false;
	fi->rdc.version++;
	fi->rdc.size = 0;
	fi->rdc.pos = 0;
}