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
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 

__attribute__((used)) static obs_properties_t *libfdk_properties(void *unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t *props = obs_properties_create();

	obs_properties_add_int(props, "bitrate", obs_module_text("Bitrate"), 32,
			       1024, 32);
	obs_properties_add_bool(props, "afterburner",
				obs_module_text("Afterburner"));

	return props;
}