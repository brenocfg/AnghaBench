#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct serializer {int dummy; } ;
struct font_path_info {int full_len; int face_len; int is_bitmap; int num_sizes; int bold; int italic; int index; int /*<<< orphan*/  path; int /*<<< orphan*/  sizes; int /*<<< orphan*/  face_and_style; } ;
struct TYPE_2__ {size_t num; struct font_path_info* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  do_write (int) ; 
 int /*<<< orphan*/  file_output_serializer_free (struct serializer*) ; 
 int file_output_serializer_init_safe (struct serializer*,char*,char*) ; 
 int font_cache_ver ; 
 TYPE_1__ font_list ; 
 int get_font_checksum () ; 
 char* obs_module_config_path (char*) ; 
 int write_data (struct serializer*,int /*<<< orphan*/ ,int) ; 
 int write_str (struct serializer*,int /*<<< orphan*/ ) ; 
 int write_var (struct serializer*,int) ; 

void save_font_list(void)
{
	char *file_name = obs_module_config_path("font_data.bin");
	uint32_t font_checksum = get_font_checksum();
	int font_count = (int)font_list.num;
	struct serializer s;
	bool success = false;

	if (font_checksum)
		success =
			file_output_serializer_init_safe(&s, file_name, "tmp");
	bfree(file_name);

	if (!success)
		return;

	success = write_var(&s, font_cache_ver);
	if (!success)
		return;
	success = write_var(&s, font_checksum);
	if (!success)
		return;
	success = write_var(&s, font_count);
	if (!success)
		return;

#define do_write(var)                 \
	success = write_var(&s, var); \
	if (!success)                 \
	break

	for (size_t i = 0; i < font_list.num; i++) {
		struct font_path_info *info = &font_list.array[i];

		success = write_str(&s, info->face_and_style);
		if (!success)
			break;

		do_write(info->full_len);
		do_write(info->face_len);
		do_write(info->is_bitmap);
		do_write(info->num_sizes);

		success = write_data(&s, info->sizes,
				     sizeof(int) * info->num_sizes);
		if (!success)
			break;

		do_write(info->bold);

		success = write_str(&s, info->path);
		if (!success)
			break;

		do_write(info->italic);
		do_write(info->index);
	}

#undef do_write

	file_output_serializer_free(&s);
}