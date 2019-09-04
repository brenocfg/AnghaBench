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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_no_addr; } ;

/* Variables and functions */
 TYPE_1__* GFS2_I (struct inode*) ; 

__attribute__((used)) static int iget_test(struct inode *inode, void *opaque)
{
	u64 no_addr = *(u64 *)opaque;

	return GFS2_I(inode)->i_no_addr == no_addr;
}