#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct f2fs_sb_info {int blocks_per_seg; TYPE_3__* sb; } ;
struct TYPE_6__ {TYPE_2__* s_bdi; } ;
struct TYPE_4__ {scalar_t__ dirty_exceeded; } ;
struct TYPE_5__ {TYPE_1__ wb; } ;

/* Variables and functions */
 int BIO_MAX_PAGES ; 
 int DATA ; 
 int META ; 
 int NODE ; 

__attribute__((used)) static inline int nr_pages_to_skip(struct f2fs_sb_info *sbi, int type)
{
	if (sbi->sb->s_bdi->wb.dirty_exceeded)
		return 0;

	if (type == DATA)
		return sbi->blocks_per_seg;
	else if (type == NODE)
		return 8 * sbi->blocks_per_seg;
	else if (type == META)
		return 8 * BIO_MAX_PAGES;
	else
		return 0;
}