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
struct cs35l35_private {int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void cs35l35_reset(struct cs35l35_private *cs35l35)
{
	gpiod_set_value_cansleep(cs35l35->reset_gpio, 0);
	usleep_range(2000, 2100);
	gpiod_set_value_cansleep(cs35l35->reset_gpio, 1);
	usleep_range(1000, 1100);
}