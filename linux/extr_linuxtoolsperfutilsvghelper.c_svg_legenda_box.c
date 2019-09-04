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

/* Variables and functions */
 int SLOT_HEIGHT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,double,double,char const*) ; 
 int /*<<< orphan*/  svgfile ; 

__attribute__((used)) static void svg_legenda_box(int X, const char *text, const char *style)
{
	double boxsize;
	boxsize = SLOT_HEIGHT / 2;

	fprintf(svgfile, "<rect x=\"%i\" width=\"%.8f\" y=\"0\" height=\"%.1f\" class=\"%s\"/>\n",
		X, boxsize, boxsize, style);
	fprintf(svgfile, "<text transform=\"translate(%.8f, %.8f)\" font-size=\"%.8fpt\">%s</text>\n",
		X + boxsize + 5, boxsize, 0.8 * boxsize, text);
}