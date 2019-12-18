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
struct TYPE_2__ {unsigned int* utf32nfdi; unsigned int* utf32nfdicf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LINESIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf0 ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_fail (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  line_fail (char*,int /*<<< orphan*/ ) ; 
 unsigned int* malloc (int) ; 
 int /*<<< orphan*/  open_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* prop_name ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*,unsigned int*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* unicode_data ; 
 int /*<<< orphan*/  utf32valid (unsigned int) ; 
 int verbose ; 

__attribute__((used)) static void ignore_init(void)
{
	FILE *file;
	unsigned int unichar;
	unsigned int first;
	unsigned int last;
	unsigned int *um;
	int count;
	int ret;

	if (verbose > 0)
		printf("Parsing %s\n", prop_name);
	file = fopen(prop_name, "r");
	if (!file)
		open_fail(prop_name, errno);
	assert(file);
	count = 0;
	while (fgets(line, LINESIZE, file)) {
		ret = sscanf(line, "%X..%X ; %s # ", &first, &last, buf0);
		if (ret == 3) {
			if (strcmp(buf0, "Default_Ignorable_Code_Point"))
				continue;
			if (!utf32valid(first) || !utf32valid(last))
				line_fail(prop_name, line);
			for (unichar = first; unichar <= last; unichar++) {
				free(unicode_data[unichar].utf32nfdi);
				um = malloc(sizeof(unsigned int));
				*um = 0;
				unicode_data[unichar].utf32nfdi = um;
				free(unicode_data[unichar].utf32nfdicf);
				um = malloc(sizeof(unsigned int));
				*um = 0;
				unicode_data[unichar].utf32nfdicf = um;
				count++;
			}
			if (verbose > 1)
				printf(" %X..%X Default_Ignorable_Code_Point\n",
					first, last);
			continue;
		}
		ret = sscanf(line, "%X ; %s # ", &unichar, buf0);
		if (ret == 2) {
			if (strcmp(buf0, "Default_Ignorable_Code_Point"))
				continue;
			if (!utf32valid(unichar))
				line_fail(prop_name, line);
			free(unicode_data[unichar].utf32nfdi);
			um = malloc(sizeof(unsigned int));
			*um = 0;
			unicode_data[unichar].utf32nfdi = um;
			free(unicode_data[unichar].utf32nfdicf);
			um = malloc(sizeof(unsigned int));
			*um = 0;
			unicode_data[unichar].utf32nfdicf = um;
			if (verbose > 1)
				printf(" %X Default_Ignorable_Code_Point\n",
					unichar);
			count++;
			continue;
		}
	}
	fclose(file);

	if (verbose > 0)
		printf("Found %d entries\n", count);
	if (count == 0)
		file_fail(prop_name);
}