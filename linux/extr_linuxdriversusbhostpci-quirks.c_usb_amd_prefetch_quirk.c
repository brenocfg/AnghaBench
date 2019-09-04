#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ gen; } ;
struct TYPE_4__ {TYPE_1__ sb_type; } ;

/* Variables and functions */
 scalar_t__ AMD_CHIPSET_SB800 ; 
 TYPE_2__ amd_chipset ; 
 int /*<<< orphan*/  usb_amd_find_chipset_info () ; 

bool usb_amd_prefetch_quirk(void)
{
	usb_amd_find_chipset_info();
	/* SB800 needs pre-fetch fix */
	return amd_chipset.sb_type.gen == AMD_CHIPSET_SB800;
}