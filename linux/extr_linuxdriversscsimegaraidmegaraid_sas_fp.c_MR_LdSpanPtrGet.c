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
typedef  size_t u32 ;
struct MR_LD_SPAN {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ldSpanMap; } ;
struct MR_DRV_RAID_MAP_ALL {TYPE_3__ raidMap; } ;
struct TYPE_5__ {TYPE_1__* spanBlock; } ;
struct TYPE_4__ {struct MR_LD_SPAN span; } ;

/* Variables and functions */

__attribute__((used)) static struct MR_LD_SPAN *MR_LdSpanPtrGet(u32 ld, u32 span,
					  struct MR_DRV_RAID_MAP_ALL *map)
{
	return &map->raidMap.ldSpanMap[ld].spanBlock[span].span;
}