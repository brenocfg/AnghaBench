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
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_PATH_FILE ; 
 int /*<<< orphan*/  OBS_TEXT_MULTILINE ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_properties_add_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_color (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_font (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_properties_add_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  obs_properties_add_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_properties_add_text (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 

__attribute__((used)) static obs_properties_t *ft2_source_properties(void *unused)
{
	UNUSED_PARAMETER(unused);

	obs_properties_t *props = obs_properties_create();
	//obs_property_t *prop;

	// TODO:
	//	Scrolling. Can't think of a way to do it with the render
	//		targets currently being broken. (0.4.2)
	//	Better/pixel shader outline/drop shadow
	//	Some way to pull text files from network, I dunno

	obs_properties_add_font(props, "font", obs_module_text("Font"));

	obs_properties_add_text(props, "text", obs_module_text("Text"),
				OBS_TEXT_MULTILINE);

	obs_properties_add_bool(props, "from_file",
				obs_module_text("ReadFromFile"));

	obs_properties_add_bool(props, "log_mode",
				obs_module_text("ChatLogMode"));

	obs_properties_add_int(props, "log_lines",
			       obs_module_text("ChatLogLines"), 1, 1000, 1);

	obs_properties_add_path(props, "text_file", obs_module_text("TextFile"),
				OBS_PATH_FILE,
				obs_module_text("TextFileFilter"), NULL);

	obs_properties_add_color(props, "color1", obs_module_text("Color1"));

	obs_properties_add_color(props, "color2", obs_module_text("Color2"));

	obs_properties_add_bool(props, "outline", obs_module_text("Outline"));

	obs_properties_add_bool(props, "drop_shadow",
				obs_module_text("DropShadow"));

	obs_properties_add_int(props, "custom_width",
			       obs_module_text("CustomWidth"), 0, 4096, 1);

	obs_properties_add_bool(props, "word_wrap",
				obs_module_text("WordWrap"));

	return props;
}