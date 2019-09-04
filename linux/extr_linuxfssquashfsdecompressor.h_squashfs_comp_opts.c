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
struct squashfs_sb_info {TYPE_1__* decompressor; } ;
struct TYPE_2__ {void* (* comp_opts ) (struct squashfs_sb_info*,void*,int) ;} ;

/* Variables and functions */
 void* stub1 (struct squashfs_sb_info*,void*,int) ; 

__attribute__((used)) static inline void *squashfs_comp_opts(struct squashfs_sb_info *msblk,
							void *buff, int length)
{
	return msblk->decompressor->comp_opts ?
		msblk->decompressor->comp_opts(msblk, buff, length) : NULL;
}