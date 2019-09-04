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
 scalar_t__ close_table ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void print_events_table_suffix(FILE *outfp)
{
	fprintf(outfp, "{\n");

	fprintf(outfp, "\t.name = 0,\n");
	fprintf(outfp, "\t.event = 0,\n");
	fprintf(outfp, "\t.desc = 0,\n");

	fprintf(outfp, "},\n");
	fprintf(outfp, "};\n");
	close_table = 0;
}