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
 int /*<<< orphan*/  _Exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_mapping_table_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_mapping_table_suffix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prog ; 

__attribute__((used)) static void create_empty_mapping(const char *output_file)
{
	FILE *outfp;

	pr_info("%s: Creating empty pmu_events_map[] table\n", prog);

	/* Truncate file to clear any partial writes to it */
	outfp = fopen(output_file, "w");
	if (!outfp) {
		perror("fopen()");
		_Exit(1);
	}

	fprintf(outfp, "#include \"pmu-events/pmu-events.h\"\n");
	print_mapping_table_prefix(outfp);
	print_mapping_table_suffix(outfp);
	fclose(outfp);
}