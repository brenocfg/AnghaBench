#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int* utf32nfdi; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LINESIZE ; 
 char* buf0 ; 
 char* data_name ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_fail (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ ignore_compatibility_form (char*) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  line_fail (char*,int /*<<< orphan*/ ) ; 
 unsigned int* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 
 int /*<<< orphan*/  open_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_utf32nfdi (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*,char*) ; 
 unsigned int strtoul (char*,char**,int) ; 
 TYPE_1__* unicode_data ; 
 int /*<<< orphan*/  utf32valid (unsigned int) ; 
 int verbose ; 

__attribute__((used)) static void nfdi_init(void)
{
	FILE *file;
	unsigned int unichar;
	unsigned int mapping[19]; /* Magic - guaranteed not to be exceeded. */
	char *s;
	char *type;
	unsigned int *um;
	int count;
	int i;
	int ret;

	if (verbose > 0)
		printf("Parsing %s\n", data_name);
	file = fopen(data_name, "r");
	if (!file)
		open_fail(data_name, errno);

	count = 0;
	while (fgets(line, LINESIZE, file)) {
		ret = sscanf(line, "%X;%*[^;];%*[^;];%*[^;];%*[^;];%[^;];",
			     &unichar, buf0);
		if (ret != 2)
			continue;
		if (!utf32valid(unichar))
			line_fail(data_name, line);

		s = buf0;
		/* skip over <tag> */
		if (*s == '<') {
			type = ++s;
			while (*++s != '>');
			*s++ = '\0';
			if(ignore_compatibility_form(type))
				continue;
		}
		/* decode the decomposition into UTF-32 */
		i = 0;
		while (*s) {
			mapping[i] = strtoul(s, &s, 16);
			if (!utf32valid(mapping[i]))
				line_fail(data_name, line);
			i++;
		}
		mapping[i++] = 0;

		um = malloc(i * sizeof(unsigned int));
		memcpy(um, mapping, i * sizeof(unsigned int));
		unicode_data[unichar].utf32nfdi = um;

		if (verbose > 1)
			print_utf32nfdi(unichar);
		count++;
	}
	fclose(file);
	if (verbose > 0)
		printf("Found %d entries\n", count);
	if (count == 0)
		file_fail(data_name);
}