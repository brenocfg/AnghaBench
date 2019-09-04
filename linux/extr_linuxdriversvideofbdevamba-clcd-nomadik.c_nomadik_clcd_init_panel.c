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
struct device_node {int dummy; } ;
struct clcd_fb {TYPE_1__* dev; int /*<<< orphan*/  board; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  tpg110_init (int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 

int nomadik_clcd_init_panel(struct clcd_fb *fb, struct device_node *panel)
{
	if (of_device_is_compatible(panel, "tpo,tpg110"))
		tpg110_init(&fb->dev->dev, panel, fb->board);
	else
		dev_info(&fb->dev->dev, "unknown panel\n");

	/* Unknown panel, fall through */
	return 0;
}