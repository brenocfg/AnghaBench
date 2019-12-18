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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* bzalloc (size_t) ; 

__attribute__((used)) static char *wide_to_utf8(const wchar_t *str, size_t len)
{
	size_t utf8_len;
	char *utf8_str = NULL;

	utf8_len = (size_t)WideCharToMultiByte(CP_UTF8, 0, str, (int)len, NULL,
					       0, NULL, false);
	if (utf8_len) {
		utf8_str = bzalloc(utf8_len + 1);
		utf8_len = (size_t)WideCharToMultiByte(CP_UTF8, 0, str,
						       (int)len, utf8_str,
						       (int)utf8_len + 1, NULL,
						       false);

		if (!utf8_len) {
			bfree(utf8_str);
			utf8_str = NULL;
		}
	}

	return utf8_str;
}