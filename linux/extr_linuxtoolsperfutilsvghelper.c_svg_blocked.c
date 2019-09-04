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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  svg_box (int,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  svgfile ; 
 char* time_to_string (scalar_t__) ; 

void svg_blocked(int Yslot, int cpu, u64 start, u64 end, const char *backtrace)
{
	if (!svgfile)
		return;

	fprintf(svgfile, "<g>\n");
	fprintf(svgfile, "<title>#%d blocked %s</title>\n", cpu,
		time_to_string(end - start));
	if (backtrace)
		fprintf(svgfile, "<desc>Blocked on:\n%s</desc>\n", backtrace);
	svg_box(Yslot, start, end, "blocked");
	fprintf(svgfile, "</g>\n");
}