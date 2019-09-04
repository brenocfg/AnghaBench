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
 double MIN_TEXT_SIZE ; 
 double SLOT_HEIGHT ; 
 int SLOT_MULT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 double round_text_size (double) ; 
 scalar_t__ svg_highlight ; 
 int /*<<< orphan*/  svgfile ; 
 double time2pixels (scalar_t__) ; 
 char* time_to_string (scalar_t__) ; 

void svg_running(int Yslot, int cpu, u64 start, u64 end, const char *backtrace)
{
	double text_size;
	const char *type;

	if (!svgfile)
		return;

	if (svg_highlight && end - start > svg_highlight)
		type = "sample_hi";
	else
		type = "sample";
	fprintf(svgfile, "<g>\n");

	fprintf(svgfile, "<title>#%d running %s</title>\n",
		cpu, time_to_string(end - start));
	if (backtrace)
		fprintf(svgfile, "<desc>Switched because:\n%s</desc>\n", backtrace);
	fprintf(svgfile, "<rect x=\"%.8f\" width=\"%.8f\" y=\"%.1f\" height=\"%.1f\" class=\"%s\"/>\n",
		time2pixels(start), time2pixels(end)-time2pixels(start), Yslot * SLOT_MULT, SLOT_HEIGHT,
		type);

	text_size = (time2pixels(end)-time2pixels(start));
	if (cpu > 9)
		text_size = text_size/2;
	if (text_size > 1.25)
		text_size = 1.25;
	text_size = round_text_size(text_size);

	if (text_size > MIN_TEXT_SIZE)
		fprintf(svgfile, "<text x=\"%.8f\" y=\"%.8f\" font-size=\"%.8fpt\">%i</text>\n",
			time2pixels(start), Yslot *  SLOT_MULT + SLOT_HEIGHT - 1, text_size,  cpu + 1);

	fprintf(svgfile, "</g>\n");
}