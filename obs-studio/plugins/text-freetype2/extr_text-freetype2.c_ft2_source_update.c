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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct ft2_source {int custom_width; int word_wrap; int* color; int log_lines; int log_mode; scalar_t__ font_size; int from_file; int file_load_failed; char const* font_name; char const* font_style; int font_flags; char* texbuf; char* text; char const* text_file; int /*<<< orphan*/ * font_face; int /*<<< orphan*/  last_checked; scalar_t__ max_h; int /*<<< orphan*/ * draw_effect; void* outline_text; void* drop_shadow; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ENCODING_UNICODE ; 
 int /*<<< orphan*/  FT_Select_Charmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_Set_Pixel_Sizes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*) ; 
 void* bstrdup (char const*) ; 
 char* bzalloc (int) ; 
 int /*<<< orphan*/  cache_glyphs (struct ft2_source*,char*) ; 
 int /*<<< orphan*/  cache_standard_glyphs (struct ft2_source*) ; 
 int /*<<< orphan*/ * ft2_lib ; 
 int /*<<< orphan*/ * gs_effect_create_from_file (char*,char**) ; 
 int /*<<< orphan*/  init_font (struct ft2_source*) ; 
 int /*<<< orphan*/  load_text_from_file (struct ft2_source*,char const*) ; 
 void* obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_data_get_obj (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 char* obs_module_file (char*) ; 
 int /*<<< orphan*/  os_file_exists (char const*) ; 
 int /*<<< orphan*/  os_gettime_ns () ; 
 int /*<<< orphan*/  os_utf8_to_wcs_ptr (char const*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  read_from_end (struct ft2_source*,char const*) ; 
 int /*<<< orphan*/  set_up_vertex_buffer (struct ft2_source*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int texbuf_h ; 
 int texbuf_w ; 

__attribute__((used)) static void ft2_source_update(void *data, obs_data_t *settings)
{
	struct ft2_source *srcdata = data;
	obs_data_t *font_obj = obs_data_get_obj(settings, "font");
	bool vbuf_needs_update = false;
	bool word_wrap = false;
	uint32_t color[2];
	uint32_t custom_width = 0;

	const char *font_name = obs_data_get_string(font_obj, "face");
	const char *font_style = obs_data_get_string(font_obj, "style");
	uint16_t font_size = (uint16_t)obs_data_get_int(font_obj, "size");
	uint32_t font_flags = (uint32_t)obs_data_get_int(font_obj, "flags");

	if (!font_obj)
		return;

	srcdata->drop_shadow = obs_data_get_bool(settings, "drop_shadow");
	srcdata->outline_text = obs_data_get_bool(settings, "outline");
	word_wrap = obs_data_get_bool(settings, "word_wrap");

	color[0] = (uint32_t)obs_data_get_int(settings, "color1");
	color[1] = (uint32_t)obs_data_get_int(settings, "color2");

	custom_width = (uint32_t)obs_data_get_int(settings, "custom_width");
	if (custom_width >= 100) {
		if (custom_width != srcdata->custom_width) {
			srcdata->custom_width = custom_width;
			vbuf_needs_update = true;
		}
	} else {
		if (srcdata->custom_width >= 100)
			vbuf_needs_update = true;
		srcdata->custom_width = 0;
	}

	if (word_wrap != srcdata->word_wrap) {
		srcdata->word_wrap = word_wrap;
		vbuf_needs_update = true;
	}

	if (color[0] != srcdata->color[0] || color[1] != srcdata->color[1]) {
		srcdata->color[0] = color[0];
		srcdata->color[1] = color[1];
		vbuf_needs_update = true;
	}

	bool from_file = obs_data_get_bool(settings, "from_file");
	bool chat_log_mode = obs_data_get_bool(settings, "log_mode");
	uint32_t log_lines = (uint32_t)obs_data_get_int(settings, "log_lines");

	if (srcdata->log_lines != log_lines) {
		srcdata->log_lines = log_lines;
		vbuf_needs_update = true;
	}
	srcdata->log_mode = chat_log_mode;

	if (ft2_lib == NULL)
		goto error;

	if (srcdata->draw_effect == NULL) {
		char *effect_file = NULL;
		char *error_string = NULL;

		effect_file = obs_module_file("text_default.effect");

		if (effect_file) {
			obs_enter_graphics();
			srcdata->draw_effect = gs_effect_create_from_file(
				effect_file, &error_string);
			obs_leave_graphics();

			bfree(effect_file);
			if (error_string != NULL)
				bfree(error_string);
		}
	}

	if (srcdata->font_size != font_size || srcdata->from_file != from_file)
		vbuf_needs_update = true;

	srcdata->file_load_failed = false;
	srcdata->from_file = from_file;

	if (srcdata->font_name != NULL) {
		if (strcmp(font_name, srcdata->font_name) == 0 &&
		    strcmp(font_style, srcdata->font_style) == 0 &&
		    font_flags == srcdata->font_flags &&
		    font_size == srcdata->font_size)
			goto skip_font_load;

		bfree(srcdata->font_name);
		bfree(srcdata->font_style);
		srcdata->font_name = NULL;
		srcdata->font_style = NULL;
		srcdata->max_h = 0;
		vbuf_needs_update = true;
	}

	srcdata->font_name = bstrdup(font_name);
	srcdata->font_style = bstrdup(font_style);
	srcdata->font_size = font_size;
	srcdata->font_flags = font_flags;

	if (!init_font(srcdata) || srcdata->font_face == NULL) {
		blog(LOG_WARNING, "FT2-text: Failed to load font %s",
		     srcdata->font_name);
		goto error;
	} else {
		FT_Set_Pixel_Sizes(srcdata->font_face, 0, srcdata->font_size);
		FT_Select_Charmap(srcdata->font_face, FT_ENCODING_UNICODE);
	}

	if (srcdata->texbuf != NULL) {
		bfree(srcdata->texbuf);
		srcdata->texbuf = NULL;
	}
	srcdata->texbuf = bzalloc(texbuf_w * texbuf_h);

	if (srcdata->font_face)
		cache_standard_glyphs(srcdata);

skip_font_load:
	if (from_file) {
		const char *tmp = obs_data_get_string(settings, "text_file");

		if (!tmp || !*tmp || !os_file_exists(tmp)) {
			const char *emptystr = " ";

			bfree(srcdata->text);
			srcdata->text = NULL;

			os_utf8_to_wcs_ptr(emptystr, strlen(emptystr),
					   &srcdata->text);
			blog(LOG_WARNING,
			     "FT2-text: Failed to open %s for "
			     "reading",
			     tmp);
		} else {
			if (srcdata->text_file != NULL &&
			    strcmp(srcdata->text_file, tmp) == 0 &&
			    !vbuf_needs_update)
				goto error;

			bfree(srcdata->text_file);

			srcdata->text_file = bstrdup(tmp);
			if (chat_log_mode)
				read_from_end(srcdata, tmp);
			else
				load_text_from_file(srcdata, tmp);
			srcdata->last_checked = os_gettime_ns();
		}
	} else {
		const char *tmp = obs_data_get_string(settings, "text");
		if (!tmp || !*tmp)
			goto error;

		if (srcdata->text != NULL) {
			bfree(srcdata->text);
			srcdata->text = NULL;
		}

		os_utf8_to_wcs_ptr(tmp, strlen(tmp), &srcdata->text);
	}

	if (srcdata->font_face) {
		cache_glyphs(srcdata, srcdata->text);
		set_up_vertex_buffer(srcdata);
	}

error:
	obs_data_release(font_obj);
}