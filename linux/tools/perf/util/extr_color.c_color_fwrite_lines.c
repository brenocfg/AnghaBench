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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char const* PERF_COLOR_RESET ; 
 scalar_t__ fputc (char,int /*<<< orphan*/ *) ; 
 scalar_t__ fputs (char const*,int /*<<< orphan*/ *) ; 
 int fwrite (char const*,size_t,int,int /*<<< orphan*/ *) ; 
 char* memchr (char const*,char,size_t) ; 

int color_fwrite_lines(FILE *fp, const char *color,
		size_t count, const char *buf)
{
	if (!*color)
		return fwrite(buf, count, 1, fp) != 1;

	while (count) {
		char *p = memchr(buf, '\n', count);

		if (p != buf && (fputs(color, fp) < 0 ||
				fwrite(buf, p ? (size_t)(p - buf) : count, 1, fp) != 1 ||
				fputs(PERF_COLOR_RESET, fp) < 0))
			return -1;
		if (!p)
			return 0;
		if (fputc('\n', fp) < 0)
			return -1;
		count -= p + 1 - buf;
		buf = p + 1;
	}
	return 0;
}