#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  loaded; } ;
struct TYPE_6__ {TYPE_1__ image; } ;
struct image_source {char* file; TYPE_2__ if2; scalar_t__ update_time_elapsed; int /*<<< orphan*/  file_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,char*) ; 
 int /*<<< orphan*/  get_modified_timestamp (char*) ; 
 int /*<<< orphan*/  gs_image_file2_free (TYPE_2__*) ; 
 int /*<<< orphan*/  gs_image_file2_init (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  gs_image_file2_init_texture (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void image_source_load(struct image_source *context)
{
	char *file = context->file;

	obs_enter_graphics();
	gs_image_file2_free(&context->if2);
	obs_leave_graphics();

	if (file && *file) {
		debug("loading texture '%s'", file);
		context->file_timestamp = get_modified_timestamp(file);
		gs_image_file2_init(&context->if2, file);
		context->update_time_elapsed = 0;

		obs_enter_graphics();
		gs_image_file2_init_texture(&context->if2);
		obs_leave_graphics();

		if (!context->if2.image.loaded)
			warn("failed to load texture '%s'", file);
	}
}