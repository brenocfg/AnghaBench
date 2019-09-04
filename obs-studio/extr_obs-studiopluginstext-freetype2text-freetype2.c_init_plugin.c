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
 int /*<<< orphan*/  FT_Init_FreeType (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ft2_lib ; 
 int /*<<< orphan*/  load_cached_os_font_list () ; 
 int /*<<< orphan*/  load_os_font_list () ; 
 int plugin_initialized ; 

__attribute__((used)) static void init_plugin(void)
{
	if (plugin_initialized)
		return;

	FT_Init_FreeType(&ft2_lib);

	if (ft2_lib == NULL) {
		blog(LOG_WARNING, "FT2-text: Failed to initialize FT2.");
		return;
	}

	if (!load_cached_os_font_list())
		load_os_font_list();

	plugin_initialized = true;
}