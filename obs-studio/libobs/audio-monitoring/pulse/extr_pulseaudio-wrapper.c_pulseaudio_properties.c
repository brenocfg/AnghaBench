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
typedef  int /*<<< orphan*/  pa_proplist ;

/* Variables and functions */
 int /*<<< orphan*/  PA_PROP_APPLICATION_ICON_NAME ; 
 int /*<<< orphan*/  PA_PROP_APPLICATION_NAME ; 
 int /*<<< orphan*/  PA_PROP_MEDIA_ROLE ; 
 int /*<<< orphan*/ * pa_proplist_new () ; 
 int /*<<< orphan*/  pa_proplist_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static pa_proplist *pulseaudio_properties()
{
	pa_proplist *p = pa_proplist_new();

	pa_proplist_sets(p, PA_PROP_APPLICATION_NAME, "OBS");
	pa_proplist_sets(p, PA_PROP_APPLICATION_ICON_NAME, "obs");
	pa_proplist_sets(p, PA_PROP_MEDIA_ROLE, "production");

	return p;
}