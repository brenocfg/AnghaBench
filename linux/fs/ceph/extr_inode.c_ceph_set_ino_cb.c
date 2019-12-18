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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct ceph_vino {int dummy; } ;
struct TYPE_2__ {struct ceph_vino i_vino; } ;

/* Variables and functions */
 TYPE_1__* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  ceph_vino_to_ino (struct ceph_vino) ; 
 int /*<<< orphan*/  inode_set_iversion_raw (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceph_set_ino_cb(struct inode *inode, void *data)
{
	ceph_inode(inode)->i_vino = *(struct ceph_vino *)data;
	inode->i_ino = ceph_vino_to_ino(*(struct ceph_vino *)data);
	inode_set_iversion_raw(inode, 0);
	return 0;
}