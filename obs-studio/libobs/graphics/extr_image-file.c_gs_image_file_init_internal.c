#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {int cx; int cy; int loaded; int /*<<< orphan*/  texture_data; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ gs_image_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  gs_create_texture_file_data (char const*,int /*<<< orphan*/ *,int*,int*) ; 
 int gs_get_format_bpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_image_file_free (TYPE_1__*) ; 
 scalar_t__ init_animated_gif (TYPE_1__*,char const*,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void gs_image_file_init_internal(gs_image_file_t *image,
					const char *file, uint64_t *mem_usage)
{
	size_t len;

	if (!image)
		return;

	memset(image, 0, sizeof(*image));

	if (!file)
		return;

	len = strlen(file);

	if (len > 4 && strcmp(file + len - 4, ".gif") == 0) {
		if (init_animated_gif(image, file, mem_usage))
			return;
	}

	image->texture_data = gs_create_texture_file_data(
		file, &image->format, &image->cx, &image->cy);

	if (mem_usage) {
		*mem_usage += image->cx * image->cy *
			      gs_get_format_bpp(image->format) / 8;
	}

	image->loaded = !!image->texture_data;
	if (!image->loaded) {
		blog(LOG_WARNING, "Failed to load file '%s'", file);
		gs_image_file_free(image);
	}
}