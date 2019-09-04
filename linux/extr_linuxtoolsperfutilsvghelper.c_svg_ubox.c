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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 double SLOT_HALF ; 
 int SLOT_MULT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 double normalize_height (double) ; 
 int /*<<< orphan*/  svgfile ; 
 double time2pixels (int /*<<< orphan*/ ) ; 

void svg_ubox(int Yslot, u64 start, u64 end, double height, const char *type, int fd, int err, int merges)
{
	double w = time2pixels(end) - time2pixels(start);
	height = normalize_height(height);

	if (!svgfile)
		return;

	fprintf(svgfile, "<g>\n");
	fprintf(svgfile, "<title>fd=%d error=%d merges=%d</title>\n", fd, err, merges);
	fprintf(svgfile, "<rect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" class=\"%s\"/>\n",
		time2pixels(start),
		w,
		Yslot * SLOT_MULT,
		SLOT_HALF * height,
		type);
	fprintf(svgfile, "</g>\n");
}