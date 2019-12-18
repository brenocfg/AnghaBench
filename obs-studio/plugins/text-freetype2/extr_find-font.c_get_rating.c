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
struct font_path_info {char* face_and_style; } ;
struct dstr {char* array; } ;

/* Variables and functions */
 scalar_t__ toupper (char const) ; 

__attribute__((used)) static inline size_t get_rating(struct font_path_info *info, struct dstr *cmp)
{
	const char *src = info->face_and_style;
	const char *dst = cmp->array;
	size_t num = 0;

	do {
		char ch1 = (char)toupper(*src);
		char ch2 = (char)toupper(*dst);

		if (ch1 != ch2)
			break;

		num++;
	} while (*src++ && *dst++);

	return num;
}