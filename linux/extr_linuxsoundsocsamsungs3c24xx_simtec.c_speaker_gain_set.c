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
struct TYPE_2__ {int /*<<< orphan*/ * amp_gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pdata ; 

__attribute__((used)) static void speaker_gain_set(int value)
{
	gpio_set_value_cansleep(pdata->amp_gain[0], value & 1);
	gpio_set_value_cansleep(pdata->amp_gain[1], value >> 1);
}