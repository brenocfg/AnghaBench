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
struct cifs_fattr {int /*<<< orphan*/  cf_createtime; int /*<<< orphan*/  cf_uniqueid; } ;
struct TYPE_2__ {int /*<<< orphan*/  createtime; int /*<<< orphan*/  uniqueid; } ;

/* Variables and functions */
 TYPE_1__* CIFS_I (struct inode*) ; 

__attribute__((used)) static int
cifs_init_inode(struct inode *inode, void *opaque)
{
	struct cifs_fattr *fattr = (struct cifs_fattr *) opaque;

	CIFS_I(inode)->uniqueid = fattr->cf_uniqueid;
	CIFS_I(inode)->createtime = fattr->cf_createtime;
	return 0;
}