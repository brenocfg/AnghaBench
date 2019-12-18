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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct obs_video_info {int fps_den; int fps_num; int base_width; int base_height; int output_width; int output_height; int /*<<< orphan*/  output_format; } ;
struct dstr {size_t len; char* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  convert ;

/* Variables and functions */
 scalar_t__ astrcmp_n (char const*,char const*,int) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_cat_ch (struct dstr*,char) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_mid (struct dstr*,struct dstr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  erase_ch (struct dstr*,size_t) ; 
 int /*<<< orphan*/  get_video_format_name (int /*<<< orphan*/ ) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_get_video_info (struct obs_video_info*) ; 
 int /*<<< orphan*/  replace_text (struct dstr*,size_t,int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,double const,...) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strftime (char*,int,char const*,struct tm*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 scalar_t__ valid_string (char*) ; 

char *os_generate_formatted_filename(const char *extension, bool space,
				     const char *format)
{
	time_t now = time(0);
	struct tm *cur_time;
	cur_time = localtime(&now);
	struct obs_video_info ovi;
	obs_get_video_info(&ovi);

	const size_t spec_count = 23;
	static const char *spec[][2] = {
		{"%CCYY", "%Y"}, {"%YY", "%y"}, {"%MM", "%m"}, {"%DD", "%d"},
		{"%hh", "%H"},   {"%mm", "%M"}, {"%ss", "%S"}, {"%%", "%%"},

		{"%a", ""},      {"%A", ""},    {"%b", ""},    {"%B", ""},
		{"%d", ""},      {"%H", ""},    {"%I", ""},    {"%m", ""},
		{"%M", ""},      {"%p", ""},    {"%S", ""},    {"%y", ""},
		{"%Y", ""},      {"%z", ""},    {"%Z", ""},
	};

	char convert[128] = {0};
	struct dstr sf;
	struct dstr c = {0};
	size_t pos = 0;

	dstr_init_copy(&sf, format);

	while (pos < sf.len) {
		const char *cmp = sf.array + pos;
		for (size_t i = 0; i < spec_count && !convert[0]; i++) {
			size_t len = strlen(spec[i][0]);

			if (astrcmp_n(cmp, spec[i][0], len) == 0) {
				if (strlen(spec[i][1]))
					strftime(convert, sizeof(convert),
						 spec[i][1], cur_time);
				else
					strftime(convert, sizeof(convert),
						 spec[i][0], cur_time);

				dstr_copy(&c, convert);
				if (c.len && valid_string(c.array))
					replace_text(&sf, pos, len, convert);
			}
		}

		if (!convert[0]) {
			if (astrcmp_n(cmp, "%FPS", 4) == 0) {
				if (ovi.fps_den <= 1) {
					sprintf(convert, "%u", ovi.fps_num);
				} else {
					const double obsFPS =
						(double)ovi.fps_num /
						(double)ovi.fps_den;
					sprintf(convert, "%.2f", obsFPS);
				}
				replace_text(&sf, pos, 4, convert);

			} else if (astrcmp_n(cmp, "%CRES", 5) == 0) {
				sprintf(convert, "%ux%u", ovi.base_width,
					ovi.base_height);
				replace_text(&sf, pos, 5, convert);

			} else if (astrcmp_n(cmp, "%ORES", 5) == 0) {
				sprintf(convert, "%ux%u", ovi.output_width,
					ovi.output_height);
				replace_text(&sf, pos, 5, convert);

			} else if (astrcmp_n(cmp, "%VF", 3) == 0) {
				strcpy(convert, get_video_format_name(
							ovi.output_format));
				replace_text(&sf, pos, 3, convert);
			}
		}

		if (convert[0]) {
			pos += strlen(convert);
			convert[0] = 0;
		} else if (!convert[0] && sf.array[pos] == '%') {
			erase_ch(&sf, pos);
		} else {
			pos++;
		}
	}

	if (!space)
		dstr_replace(&sf, " ", "_");

	dstr_cat_ch(&sf, '.');
	dstr_cat(&sf, extension);
	dstr_free(&c);

	if (sf.len > 255)
		dstr_mid(&sf, &sf, 0, 255);

	return sf.array;
}