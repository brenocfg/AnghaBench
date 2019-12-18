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
typedef  void* uint32_t ;
struct font_path_info {int is_bitmap; int bold; int italic; int /*<<< orphan*/  path; int /*<<< orphan*/  index; void* face_len; void* full_len; int /*<<< orphan*/  face_and_style; } ;
struct dstr {scalar_t__ len; int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int face_flags; int style_flags; scalar_t__ style_name; } ;
typedef  int /*<<< orphan*/  FT_Long ;
typedef  TYPE_1__* FT_Face ;

/* Variables and functions */
 int FT_FACE_FLAG_FIXED_SIZES ; 
 int FT_STYLE_FLAG_BOLD ; 
 int FT_STYLE_FLAG_ITALIC ; 
 int /*<<< orphan*/  bstrdup (char const*) ; 
 int /*<<< orphan*/  create_bitmap_sizes (struct font_path_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct font_path_info*) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_cat_dstr (struct dstr*,struct dstr*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_depad (struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  font_list ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void add_font_path(FT_Face face, FT_Long idx, const char *family_in,
			  const char *style_in, const char *path)
{
	struct dstr face_and_style = {0};
	struct font_path_info info;

	if (!family_in || !path)
		return;

	dstr_copy(&face_and_style, family_in);
	if (face->style_name) {
		struct dstr style = {0};

		dstr_copy(&style, style_in);
		dstr_replace(&style, "Bold", "");
		dstr_replace(&style, "Italic", "");
		dstr_replace(&style, "  ", " ");
		dstr_depad(&style);

		if (!dstr_is_empty(&style)) {
			dstr_cat(&face_and_style, " ");
			dstr_cat_dstr(&face_and_style, &style);
		}

		dstr_free(&style);
	}

	info.face_and_style = face_and_style.array;
	info.full_len = (uint32_t)face_and_style.len;
	info.face_len = (uint32_t)strlen(family_in);

	info.is_bitmap = !!(face->face_flags & FT_FACE_FLAG_FIXED_SIZES);
	info.bold = !!(face->style_flags & FT_STYLE_FLAG_BOLD);
	info.italic = !!(face->style_flags & FT_STYLE_FLAG_ITALIC);
	info.index = idx;

	info.path = bstrdup(path);

	create_bitmap_sizes(&info, face);
	da_push_back(font_list, &info);

	/*blog(LOG_DEBUG, "name: %s\n\tstyle: %s\n\tpath: %s\n",
			family_in,
			style_in,
			path);*/
}