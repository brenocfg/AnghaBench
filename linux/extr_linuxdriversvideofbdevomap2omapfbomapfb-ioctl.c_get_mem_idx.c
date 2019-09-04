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
typedef  int u8 ;
struct omapfb_info {int id; TYPE_1__* region; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int OMAPFB_MEM_IDX_ENABLED ; 

__attribute__((used)) static u8 get_mem_idx(struct omapfb_info *ofbi)
{
	if (ofbi->id == ofbi->region->id)
		return 0;

	return OMAPFB_MEM_IDX_ENABLED | ofbi->region->id;
}