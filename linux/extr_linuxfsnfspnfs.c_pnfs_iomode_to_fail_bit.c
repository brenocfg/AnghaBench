#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ IOMODE_RW ; 
 int NFS_LAYOUT_RO_FAILED ; 
 int NFS_LAYOUT_RW_FAILED ; 

__attribute__((used)) static int
pnfs_iomode_to_fail_bit(u32 iomode)
{
	return iomode == IOMODE_RW ?
		NFS_LAYOUT_RW_FAILED : NFS_LAYOUT_RO_FAILED;
}