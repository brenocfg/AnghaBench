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
typedef  scalar_t__ erofs_nid_t ;
struct TYPE_2__ {scalar_t__ const nid; } ;

/* Variables and functions */
 TYPE_1__* EROFS_I (struct inode*) ; 

__attribute__((used)) static int erofs_ilookup_test_actor(struct inode *inode, void *opaque)
{
	const erofs_nid_t nid = *(erofs_nid_t *)opaque;

	return EROFS_I(inode)->nid == nid;
}