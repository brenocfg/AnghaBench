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
struct image_source {int persistent; int /*<<< orphan*/  source; int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstrdup (char const*) ; 
 int /*<<< orphan*/  image_source_load (void*) ; 
 int /*<<< orphan*/  image_source_unload (void*) ; 
 int obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_source_showing (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void image_source_update(void *data, obs_data_t *settings)
{
	struct image_source *context = data;
	const char *file = obs_data_get_string(settings, "file");
	const bool unload = obs_data_get_bool(settings, "unload");

	if (context->file)
		bfree(context->file);
	context->file = bstrdup(file);
	context->persistent = !unload;

	/* Load the image if the source is persistent or showing */
	if (context->persistent || obs_source_showing(context->source))
		image_source_load(data);
	else
		image_source_unload(data);
}