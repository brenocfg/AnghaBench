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
typedef  int /*<<< orphan*/  obs_source_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * obs_source_create_private (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static obs_source_t *create_source_from_file(const char *file)
{
	obs_data_t *settings = obs_data_create();
	obs_source_t *source;

	obs_data_set_string(settings, "file", file);
	obs_data_set_bool(settings, "unload", false);
	source = obs_source_create_private("image_source", NULL, settings);

	obs_data_release(settings);
	return source;
}