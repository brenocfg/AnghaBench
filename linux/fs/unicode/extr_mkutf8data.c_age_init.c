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
struct TYPE_2__ {int gen; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LINESIZE ; 
 int MAXGEN ; 
 unsigned int UNICODE_AGE (unsigned int,unsigned int,unsigned int) ; 
 char* age_name ; 
 int /*<<< orphan*/  age_valid (unsigned int,unsigned int,unsigned int) ; 
 unsigned int* ages ; 
 int ages_count ; 
 unsigned int* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_fail (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  line_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int sscanf (int /*<<< orphan*/ ,char*,unsigned int*,unsigned int*,...) ; 
 TYPE_1__* unicode_data ; 
 unsigned int unicode_maxage ; 
 int /*<<< orphan*/  utf32valid (unsigned int) ; 
 int verbose ; 

__attribute__((used)) static void age_init(void)
{
	FILE *file;
	unsigned int first;
	unsigned int last;
	unsigned int unichar;
	unsigned int major;
	unsigned int minor;
	unsigned int revision;
	int gen;
	int count;
	int ret;

	if (verbose > 0)
		printf("Parsing %s\n", age_name);

	file = fopen(age_name, "r");
	if (!file)
		open_fail(age_name, errno);
	count = 0;

	gen = 0;
	while (fgets(line, LINESIZE, file)) {
		ret = sscanf(line, "# Age=V%d_%d_%d",
				&major, &minor, &revision);
		if (ret == 3) {
			ages_count++;
			if (verbose > 1)
				printf(" Age V%d_%d_%d\n",
					major, minor, revision);
			if (!age_valid(major, minor, revision))
				line_fail(age_name, line);
			continue;
		}
		ret = sscanf(line, "# Age=V%d_%d", &major, &minor);
		if (ret == 2) {
			ages_count++;
			if (verbose > 1)
				printf(" Age V%d_%d\n", major, minor);
			if (!age_valid(major, minor, 0))
				line_fail(age_name, line);
			continue;
		}
	}

	/* We must have found something above. */
	if (verbose > 1)
		printf("%d age entries\n", ages_count);
	if (ages_count == 0 || ages_count > MAXGEN)
		file_fail(age_name);

	/* There is a 0 entry. */
	ages_count++;
	ages = calloc(ages_count + 1, sizeof(*ages));
	/* And a guard entry. */
	ages[ages_count] = (unsigned int)-1;

	rewind(file);
	count = 0;
	gen = 0;
	while (fgets(line, LINESIZE, file)) {
		ret = sscanf(line, "# Age=V%d_%d_%d",
				&major, &minor, &revision);
		if (ret == 3) {
			ages[++gen] =
				UNICODE_AGE(major, minor, revision);
			if (verbose > 1)
				printf(" Age V%d_%d_%d = gen %d\n",
					major, minor, revision, gen);
			if (!age_valid(major, minor, revision))
				line_fail(age_name, line);
			continue;
		}
		ret = sscanf(line, "# Age=V%d_%d", &major, &minor);
		if (ret == 2) {
			ages[++gen] = UNICODE_AGE(major, minor, 0);
			if (verbose > 1)
				printf(" Age V%d_%d = %d\n",
					major, minor, gen);
			if (!age_valid(major, minor, 0))
				line_fail(age_name, line);
			continue;
		}
		ret = sscanf(line, "%X..%X ; %d.%d #",
			     &first, &last, &major, &minor);
		if (ret == 4) {
			for (unichar = first; unichar <= last; unichar++)
				unicode_data[unichar].gen = gen;
			count += 1 + last - first;
			if (verbose > 1)
				printf("  %X..%X gen %d\n", first, last, gen);
			if (!utf32valid(first) || !utf32valid(last))
				line_fail(age_name, line);
			continue;
		}
		ret = sscanf(line, "%X ; %d.%d #", &unichar, &major, &minor);
		if (ret == 3) {
			unicode_data[unichar].gen = gen;
			count++;
			if (verbose > 1)
				printf("  %X gen %d\n", unichar, gen);
			if (!utf32valid(unichar))
				line_fail(age_name, line);
			continue;
		}
	}
	unicode_maxage = ages[gen];
	fclose(file);

	/* Nix surrogate block */
	if (verbose > 1)
		printf(" Removing surrogate block D800..DFFF\n");
	for (unichar = 0xd800; unichar <= 0xdfff; unichar++)
		unicode_data[unichar].gen = -1;

	if (verbose > 0)
	        printf("Found %d entries\n", count);
	if (count == 0)
		file_fail(age_name);
}