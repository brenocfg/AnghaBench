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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void print_mapping_table_suffix(FILE *outfp)
{
	/*
	 * Print the terminating, NULL entry.
	 */
	fprintf(outfp, "{\n");
	fprintf(outfp, "\t.cpuid = 0,\n");
	fprintf(outfp, "\t.version = 0,\n");
	fprintf(outfp, "\t.type = 0,\n");
	fprintf(outfp, "\t.table = 0,\n");
	fprintf(outfp, "},\n");

	/* and finally, the closing curly bracket for the struct */
	fprintf(outfp, "};\n");
}