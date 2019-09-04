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
typedef  int u16 ;
struct bq27xxx_device_info {int opts; } ;

/* Variables and functions */
 int BQ27000_FLAG_EDV1 ; 
 int BQ27000_FLAG_EDVF ; 
 int BQ27XXX_FLAG_SOC1 ; 
 int BQ27XXX_FLAG_SOCF ; 
 int BQ27XXX_O_ZERO ; 

__attribute__((used)) static bool bq27xxx_battery_dead(struct bq27xxx_device_info *di, u16 flags)
{
	if (di->opts & BQ27XXX_O_ZERO)
		return flags & (BQ27000_FLAG_EDV1 | BQ27000_FLAG_EDVF);
	else
		return flags & (BQ27XXX_FLAG_SOC1 | BQ27XXX_FLAG_SOCF);
}