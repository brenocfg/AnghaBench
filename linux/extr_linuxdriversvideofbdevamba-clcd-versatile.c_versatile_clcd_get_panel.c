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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct clcd_panel {TYPE_1__ mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct clcd_panel**) ; 
 struct clcd_panel** panels ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct clcd_panel *versatile_clcd_get_panel(const char *name)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(panels); i++)
		if (strcmp(panels[i]->mode.name, name) == 0)
			break;

	if (i < ARRAY_SIZE(panels))
		return panels[i];

	pr_err("CLCD: couldn't get parameters for panel %s\n", name);

	return NULL;
}