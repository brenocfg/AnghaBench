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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ k_objectid; } ;

/* Variables and functions */
 TYPE_1__* INODE_PKEY (struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int new_inode_init(struct inode *inode, struct inode *dir, umode_t mode)
{
	/*
	 * Make inode invalid - just in case we are going to drop it before
	 * the initialization happens
	 */
	INODE_PKEY(inode)->k_objectid = 0;

	/*
	 * the quota init calls have to know who to charge the quota to, so
	 * we have to set uid and gid here
	 */
	inode_init_owner(inode, dir, mode);
	return dquot_initialize(inode);
}