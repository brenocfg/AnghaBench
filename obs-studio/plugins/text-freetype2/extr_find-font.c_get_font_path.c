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
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct font_path_info {double face_len; size_t num_sizes; int bold; int italic; char* path; int /*<<< orphan*/  index; scalar_t__* sizes; scalar_t__ is_bitmap; } ;
struct dstr {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {size_t num; struct font_path_info* array; } ;
typedef  int /*<<< orphan*/  FT_Long ;

/* Variables and functions */
 size_t OBS_FONT_BOLD ; 
 size_t OBS_FONT_ITALIC ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_depad (struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 TYPE_1__ font_list ; 
 scalar_t__ get_rating (struct font_path_info*,struct dstr*) ; 

const char *get_font_path(const char *family, uint16_t size, const char *style,
			  uint32_t flags, FT_Long *idx)
{
	const char *best_path = NULL;
	double best_rating = 0.0;
	struct dstr face_and_style = {0};
	struct dstr style_str = {0};
	bool bold = !!(flags & OBS_FONT_BOLD);
	bool italic = !!(flags & OBS_FONT_ITALIC);

	if (!family || !*family)
		return NULL;

	if (style) {
		dstr_copy(&style_str, style);
		dstr_replace(&style_str, "Bold", "");
		dstr_replace(&style_str, "Italic", "");
		dstr_replace(&style_str, "  ", " ");
		dstr_depad(&style_str);
	}

	dstr_copy(&face_and_style, family);
	if (!dstr_is_empty(&style_str)) {
		dstr_cat(&face_and_style, " ");
		dstr_cat_dstr(&face_and_style, &style_str);
	}

	for (size_t i = 0; i < font_list.num; i++) {
		struct font_path_info *info = font_list.array + i;

		double rating = (double)get_rating(info, &face_and_style);
		if (rating < info->face_len)
			continue;

		if (info->is_bitmap) {
			int best_diff = 1000;
			for (uint32_t j = 0; j < info->num_sizes; j++) {
				int diff = abs(info->sizes[j] - size);
				if (diff < best_diff)
					best_diff = diff;
			}

			rating /= (double)(best_diff + 1.0);
		}

		if (info->bold == bold)
			rating += 1.0;
		if (info->italic == italic)
			rating += 1.0;

		if (rating > best_rating) {
			best_path = info->path;
			*idx = info->index;
			best_rating = rating;
		}
	}

	dstr_free(&style_str);
	dstr_free(&face_and_style);
	return best_path;
}