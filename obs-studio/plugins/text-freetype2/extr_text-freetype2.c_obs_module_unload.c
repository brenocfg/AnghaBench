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

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_FreeType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_os_font_list () ; 
 int /*<<< orphan*/  ft2_lib ; 
 scalar_t__ plugin_initialized ; 

void obs_module_unload(void)
{
	if (plugin_initialized) {
		free_os_font_list();
		FT_Done_FreeType(ft2_lib);
	}
}