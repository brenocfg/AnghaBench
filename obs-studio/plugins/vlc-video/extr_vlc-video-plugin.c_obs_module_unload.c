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
 scalar_t__ libvlc ; 
 scalar_t__ libvlc_core_module ; 
 scalar_t__ libvlc_module ; 
 int /*<<< orphan*/  libvlc_release_ (scalar_t__) ; 
 int /*<<< orphan*/  os_dlclose (scalar_t__) ; 

void obs_module_unload(void)
{
	if (libvlc)
		libvlc_release_(libvlc);
#ifdef __APPLE__
	if (libvlc_core_module)
		os_dlclose(libvlc_core_module);
#endif
	if (libvlc_module)
		os_dlclose(libvlc_module);
}