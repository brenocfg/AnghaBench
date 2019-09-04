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
struct dstr {size_t len; char* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  convert ;

/* Variables and functions */
 scalar_t__ astrcmp_n (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_cat_ch (struct dstr*,char) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_mid (struct dstr*,struct dstr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  erase_ch (struct dstr*,size_t) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replace_text (struct dstr*,size_t,size_t,char*) ; 
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

	const size_t spec_count = 23;
	static const char *spec[][2] = {
		{"%CCYY", "%Y"},
		{"%YY",   "%y"},
		{"%MM",   "%m"},
		{"%DD",   "%d"},
		{"%hh",   "%H"},
		{"%mm",   "%M"},
		{"%ss",   "%S"},
		{"%%",    "%%"},

		{"%a",    ""},
		{"%A",    ""},
		{"%b",    ""},
		{"%B",    ""},
		{"%d",    ""},
		{"%H",    ""},
		{"%I",    ""},
		{"%m",    ""},
		{"%M",    ""},
		{"%p",    ""},
		{"%S",    ""},
		{"%y",    ""},
		{"%Y",    ""},
		{"%z",    ""},
		{"%Z",    ""},
	};

	char convert[128] = {0};
	struct dstr sf;
	struct dstr c = {0};
	size_t pos = 0;

	dstr_init_copy(&sf, format);

	while (pos < sf.len) {
		for (size_t i = 0; i < spec_count && !convert[0]; i++) {
			size_t len = strlen(spec[i][0]);

			const char *cmp = sf.array + pos;

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