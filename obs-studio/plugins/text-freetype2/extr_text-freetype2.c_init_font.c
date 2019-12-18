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
struct ft2_source {int /*<<< orphan*/ * font_face; int /*<<< orphan*/  font_flags; int /*<<< orphan*/  font_style; int /*<<< orphan*/  font_size; int /*<<< orphan*/  font_name; } ;
typedef  int /*<<< orphan*/  FT_Long ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (int /*<<< orphan*/ *) ; 
 scalar_t__ FT_New_Face (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ft2_lib ; 
 char* get_font_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool init_font(struct ft2_source *srcdata)
{
	FT_Long index;
	const char *path = get_font_path(srcdata->font_name, srcdata->font_size,
					 srcdata->font_style,
					 srcdata->font_flags, &index);
	if (!path)
		return false;

	if (srcdata->font_face != NULL) {
		FT_Done_Face(srcdata->font_face);
		srcdata->font_face = NULL;
	}

	return FT_New_Face(ft2_lib, path, index, &srcdata->font_face) == 0;
}