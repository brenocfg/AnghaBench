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
typedef  int /*<<< orphan*/  obs_source_enum_proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  scene_enum_sources (void*,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void scene_enum_active_sources(void *data,
				      obs_source_enum_proc_t enum_callback,
				      void *param)
{
	scene_enum_sources(data, enum_callback, param, true);
}