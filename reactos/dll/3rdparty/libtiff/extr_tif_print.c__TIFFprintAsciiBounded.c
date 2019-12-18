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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const) ; 
 int /*<<< orphan*/  fputc (char const,int /*<<< orphan*/ *) ; 
 scalar_t__ isprint (int) ; 

__attribute__((used)) static void
_TIFFprintAsciiBounded(FILE* fd, const char* cp, size_t max_chars)
{
	for (; max_chars > 0 && *cp != '\0'; cp++, max_chars--) {
		const char* tp;

		if (isprint((int)*cp)) {
			fputc(*cp, fd);
			continue;
		}
		for (tp = "\tt\bb\rr\nn\vv"; *tp; tp++)
			if (*tp++ == *cp)
				break;
		if (*tp)
			fprintf(fd, "\\%c", *tp);
		else
			fprintf(fd, "\\%03o", *cp & 0xff);
	}
}