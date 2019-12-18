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
typedef  scalar_t__ wchar_t ;
struct TYPE_4__ {int /*<<< orphan*/  string_len; scalar_t__ string; int /*<<< orphan*/  language_id; int /*<<< orphan*/  encoding_id; int /*<<< orphan*/  platform_id; } ;
typedef  TYPE_1__ FT_SfntName ;

/* Variables and functions */
 size_t MultiByteToWideChar (unsigned int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 char* convert_utf16_be_to_utf8 (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 unsigned int get_code_page_for_font (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (size_t) ; 
 char* wide_to_utf8 (scalar_t__*,size_t) ; 

char *sfnt_name_to_utf8(FT_SfntName *sfnt_name)
{
	unsigned int code_page = get_code_page_for_font(sfnt_name->platform_id,
							sfnt_name->encoding_id,
							sfnt_name->language_id);

	char *utf8_str = NULL;
	wchar_t *utf16_str;
	size_t utf16_len;

	if (code_page == 1201)
		return convert_utf16_be_to_utf8(sfnt_name);
	else if (code_page == 0)
		return NULL;

	utf16_len = MultiByteToWideChar(code_page, 0, (char *)sfnt_name->string,
					sfnt_name->string_len, NULL, 0);
	if (utf16_len) {
		utf16_str = malloc((utf16_len + 1) * sizeof(wchar_t));
		utf16_len = MultiByteToWideChar(code_page, 0,
						(char *)sfnt_name->string,
						sfnt_name->string_len,
						utf16_str, (int)utf16_len);

		if (utf16_len) {
			utf16_str[utf16_len] = 0;
			utf8_str = wide_to_utf8(utf16_str, utf16_len);
		}

		free(utf16_str);
	}

	return utf8_str;
}