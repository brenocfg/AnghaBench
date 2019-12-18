#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct serializer {int dummy; } ;
struct font_path_info {int full_len; int face_len; int is_bitmap; int num_sizes; int bold; int italic; int index; int /*<<< orphan*/  path; int /*<<< orphan*/  sizes; int /*<<< orphan*/  face_and_style; } ;
struct TYPE_4__ {struct font_path_info* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  bmalloc (int) ; 
 int /*<<< orphan*/  da_init (TYPE_1__) ; 
 int /*<<< orphan*/  da_resize (TYPE_1__,int) ; 
 int /*<<< orphan*/  do_read (int) ; 
 TYPE_1__ font_list ; 
 int /*<<< orphan*/  free_os_font_list () ; 
 int read_data (struct serializer*,int /*<<< orphan*/ ,int) ; 
 int read_str (struct serializer*,int /*<<< orphan*/ *) ; 
 int read_var (struct serializer*,int) ; 

__attribute__((used)) static bool load_cached_font_list(struct serializer *s)
{
	bool success = true;
	int count;

	success = read_var(s, count);
	if (!success)
		return false;

	da_init(font_list);
	da_resize(font_list, count);

#define do_read(var)                \
	success = read_var(s, var); \
	if (!success)               \
	break

	for (int i = 0; i < count; i++) {
		struct font_path_info *info = &font_list.array[i];

		success = read_str(s, &info->face_and_style);
		if (!success)
			break;

		do_read(info->full_len);
		do_read(info->face_len);
		do_read(info->is_bitmap);
		do_read(info->num_sizes);

		info->sizes = bmalloc(sizeof(int) * info->num_sizes);
		success = read_data(s, info->sizes,
				    sizeof(int) * info->num_sizes);
		if (!success)
			break;

		do_read(info->bold);

		success = read_str(s, &info->path);
		if (!success)
			break;

		do_read(info->italic);
		do_read(info->index);
	}

#undef do_read

	if (!success) {
		free_os_font_list();
		return false;
	}

	return true;
}