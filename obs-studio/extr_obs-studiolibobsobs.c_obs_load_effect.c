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
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/ * gs_effect_create_from_file (char*,int /*<<< orphan*/ *) ; 
 char* obs_find_data_file (char const*) ; 

gs_effect_t *obs_load_effect(gs_effect_t **effect, const char *file)
{
	if (!*effect) {
		char *filename = obs_find_data_file(file);
		*effect = gs_effect_create_from_file(filename, NULL);
		bfree(filename);
	}

	return *effect;
}