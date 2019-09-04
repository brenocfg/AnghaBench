#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int clockrate; } ;
struct TYPE_6__ {TYPE_1__ ifcfg; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  fas216_checkmagic (TYPE_2__*) ; 

__attribute__((used)) static int fas216_syncperiod(FAS216_Info *info, int ns)
{
	int value = (info->ifcfg.clockrate * ns) / 1000;

	fas216_checkmagic(info);

	if (value < 4)
		value = 4;
	else if (value > 35)
		value = 35;

	return value & 31;
}