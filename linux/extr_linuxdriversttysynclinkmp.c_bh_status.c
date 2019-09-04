#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cts_chkcount; scalar_t__ dcd_chkcount; scalar_t__ dsr_chkcount; scalar_t__ ri_chkcount; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_BH ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bh_status(SLMP_INFO *info)
{
	if ( debug_level >= DEBUG_LEVEL_BH )
		printk( "%s(%d):%s bh_status() entry\n",
			__FILE__,__LINE__,info->device_name);

	info->ri_chkcount = 0;
	info->dsr_chkcount = 0;
	info->dcd_chkcount = 0;
	info->cts_chkcount = 0;
}