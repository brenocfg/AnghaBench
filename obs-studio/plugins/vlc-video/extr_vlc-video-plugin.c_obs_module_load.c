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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  load_libvlc_module () ; 
 int /*<<< orphan*/  load_vlc_funcs () ; 
 int /*<<< orphan*/  obs_register_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_source_info ; 

bool obs_module_load(void)
{
	if (!load_libvlc_module()) {
		blog(LOG_INFO, "Couldn't find VLC installation, VLC video "
			       "source disabled");
		return true;
	}

	if (!load_vlc_funcs())
		return true;

	blog(LOG_INFO, "VLC found, VLC video source enabled");

	obs_register_source(&vlc_source_info);
	return true;
}