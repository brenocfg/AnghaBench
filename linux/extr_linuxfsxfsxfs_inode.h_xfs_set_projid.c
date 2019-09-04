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
typedef  void* uint16_t ;
struct TYPE_2__ {void* di_projid_lo; void* di_projid_hi; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
typedef  int prid_t ;

/* Variables and functions */

__attribute__((used)) static inline void
xfs_set_projid(struct xfs_inode *ip,
		prid_t projid)
{
	ip->i_d.di_projid_hi = (uint16_t) (projid >> 16);
	ip->i_d.di_projid_lo = (uint16_t) (projid & 0xffff);
}