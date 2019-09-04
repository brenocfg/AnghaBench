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
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {int OutEpNumber; } ;

/* Variables and functions */
 int /*<<< orphan*/  _InitNormalChipOneOutEpPriority (struct adapter*) ; 
 int /*<<< orphan*/  _InitNormalChipThreeOutEpPriority (struct adapter*) ; 
 int /*<<< orphan*/  _InitNormalChipTwoOutEpPriority (struct adapter*) ; 

__attribute__((used)) static void _InitQueuePriority(struct adapter *Adapter)
{
	switch (Adapter->HalData->OutEpNumber) {
	case 1:
		_InitNormalChipOneOutEpPriority(Adapter);
		break;
	case 2:
		_InitNormalChipTwoOutEpPriority(Adapter);
		break;
	case 3:
		_InitNormalChipThreeOutEpPriority(Adapter);
		break;
	default:
		break;
	}
}