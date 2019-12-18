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
struct TYPE_2__ {unsigned int* utf32nfdicf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LINESIZE ; 
 char* buf0 ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_fail (char*) ; 
 char* fold_name ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  line_fail (char*,int /*<<< orphan*/ ) ; 
 unsigned int* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 
 int /*<<< orphan*/  open_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_utf32nfdicf (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*,char*,char*) ; 
 unsigned int strtoul (char*,char**,int) ; 
 TYPE_1__* unicode_data ; 
 int /*<<< orphan*/  utf32valid (unsigned int) ; 
 int verbose ; 

__attribute__((used)) static void nfdicf_init(void)
{
	FILE *file;
	unsigned int unichar;
	unsigned int mapping[19]; /* Magic - guaranteed not to be exceeded. */
	char status;
	char *s;
	unsigned int *um;
	int i;
	int count;
	int ret;

	if (verbose > 0)
		printf("Parsing %s\n", fold_name);
	file = fopen(fold_name, "r");
	if (!file)
		open_fail(fold_name, errno);

	count = 0;
	while (fgets(line, LINESIZE, file)) {
		ret = sscanf(line, "%X; %c; %[^;];", &unichar, &status, buf0);
		if (ret != 3)
			continue;
		if (!utf32valid(unichar))
			line_fail(fold_name, line);
		/* Use the C+F casefold. */
		if (status != 'C' && status != 'F')
			continue;
		s = buf0;
		if (*s == '<')
			while (*s++ != ' ')
				;
		i = 0;
		while (*s) {
			mapping[i] = strtoul(s, &s, 16);
			if (!utf32valid(mapping[i]))
				line_fail(fold_name, line);
			i++;
		}
		mapping[i++] = 0;

		um = malloc(i * sizeof(unsigned int));
		memcpy(um, mapping, i * sizeof(unsigned int));
		unicode_data[unichar].utf32nfdicf = um;

		if (verbose > 1)
			print_utf32nfdicf(unichar);
		count++;
	}
	fclose(file);
	if (verbose > 0)
		printf("Found %d entries\n", count);
	if (count == 0)
		file_fail(fold_name);
}