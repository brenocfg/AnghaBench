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
 double MIN_TEXT_SIZE ; 
 double SLOT_HEIGHT ; 
 double SLOT_MULT ; 
 double cpu2y (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 double round_text_size (double) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  svgfile ; 
 double time2pixels (int /*<<< orphan*/ ) ; 

void svg_cstate(int cpu, u64 start, u64 end, int type)
{
	double width;
	char style[128];

	if (!svgfile)
		return;


	fprintf(svgfile, "<g>\n");

	if (type > 6)
		type = 6;
	sprintf(style, "c%i", type);

	fprintf(svgfile, "<rect class=\"%s\" x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\"/>\n",
		style,
		time2pixels(start), time2pixels(end)-time2pixels(start),
		cpu2y(cpu), SLOT_MULT+SLOT_HEIGHT);

	width = (time2pixels(end)-time2pixels(start))/2.0;
	if (width > 6)
		width = 6;

	width = round_text_size(width);

	if (width > MIN_TEXT_SIZE)
		fprintf(svgfile, "<text x=\"%.8f\" y=\"%.8f\" font-size=\"%.8fpt\">C%i</text>\n",
			time2pixels(start), cpu2y(cpu)+width, width, type);

	fprintf(svgfile, "</g>\n");
}