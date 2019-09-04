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
typedef  int /*<<< orphan*/  u32 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ReadRFThermalMeter (struct _adapter*) ; 
 int /*<<< orphan*/  TriggerRFThermalMeter (struct _adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 

void r8712_GetThermalMeter(struct _adapter *pAdapter, u32 *value)
{
	TriggerRFThermalMeter(pAdapter);
	msleep(1000);
	*value = ReadRFThermalMeter(pAdapter);
}