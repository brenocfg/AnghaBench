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
struct TYPE_2__ {unsigned int ccc; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LINESIZE ; 
 char* ccc_name ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_fail (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  line_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*,unsigned int*,...) ; 
 TYPE_1__* unicode_data ; 
 int /*<<< orphan*/  utf32valid (unsigned int) ; 
 int verbose ; 

__attribute__((used)) static void ccc_init(void)
{
	FILE *file;
	unsigned int first;
	unsigned int last;
	unsigned int unichar;
	unsigned int value;
	int count;
	int ret;

	if (verbose > 0)
		printf("Parsing %s\n", ccc_name);

	file = fopen(ccc_name, "r");
	if (!file)
		open_fail(ccc_name, errno);

	count = 0;
	while (fgets(line, LINESIZE, file)) {
		ret = sscanf(line, "%X..%X ; %d #", &first, &last, &value);
		if (ret == 3) {
			for (unichar = first; unichar <= last; unichar++) {
				unicode_data[unichar].ccc = value;
                                count++;
			}
			if (verbose > 1)
				printf(" %X..%X ccc %d\n", first, last, value);
			if (!utf32valid(first) || !utf32valid(last))
				line_fail(ccc_name, line);
			continue;
		}
		ret = sscanf(line, "%X ; %d #", &unichar, &value);
		if (ret == 2) {
			unicode_data[unichar].ccc = value;
                        count++;
			if (verbose > 1)
				printf(" %X ccc %d\n", unichar, value);
			if (!utf32valid(unichar))
				line_fail(ccc_name, line);
			continue;
		}
	}
	fclose(file);

	if (verbose > 0)
		printf("Found %d entries\n", count);
	if (count == 0)
		file_fail(ccc_name);
}