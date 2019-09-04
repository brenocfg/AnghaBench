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
struct TYPE_2__ {int /*<<< orphan*/  safe; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int CFG_NUM ; 
 int /*<<< orphan*/  KERN_INFO ; 
 TYPE_1__* cfg_data ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ use_safe_settings ; 

__attribute__((used)) static void set_safe_settings(void)
{
	if (use_safe_settings)
	{
		int i;

		dprintkl(KERN_INFO, "Using safe settings.\n");
		for (i = 0; i < CFG_NUM; i++)
		{
			cfg_data[i].value = cfg_data[i].safe;
		}
	}
}