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
typedef  int /*<<< orphan*/  delimiters ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  format_and_print_txt (int /*<<< orphan*/ *,int,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int last_level ; 
 int /*<<< orphan*/  out_format_is_json () ; 
 scalar_t__ snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void format_and_print(FILE *outf, int level, char *header, char *value)
{
	char *spaces = "  ";
	static char delimiters[256];
	int i;

	if (!out_format_is_json()) {
		format_and_print_txt(outf, level, header, value);
		return;
	}

	if (level == 0) {
		if (header)
			fprintf(outf, "{");
		else
			fprintf(outf, "\n}\n");

	} else {
		int j = 0;

		for (i = 0; i < level; ++i)
			j += snprintf(&delimiters[j], sizeof(delimiters) - j,
				      "%s", spaces);

		if (last_level == level)
			fprintf(outf, ",\n");

		if (value) {
			if (last_level != level)
				fprintf(outf, "\n");

			fprintf(outf, "%s\"%s\": ", delimiters, header);
			fprintf(outf, "\"%s\"", value);
		} else {
			for (i = last_level - 1; i >= level; --i) {
				int k = 0;

				for (j = i; j > 0; --j)
					k += snprintf(&delimiters[k],
						      sizeof(delimiters) - k,
						      "%s", spaces);
				if (i == level && header)
					fprintf(outf, "\n%s},", delimiters);
				else
					fprintf(outf, "\n%s}", delimiters);
			}
			if (abs(last_level - level) < 3)
				fprintf(outf, "\n");
			if (header)
				fprintf(outf, "%s\"%s\": {", delimiters,
					header);
		}
	}

	last_level = level;
}