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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svg_legenda_box (int,char*,char*) ; 
 int /*<<< orphan*/  svgfile ; 

void svg_io_legenda(void)
{
	if (!svgfile)
		return;

	fprintf(svgfile, "<g>\n");
	svg_legenda_box(0,	"Disk", "disk");
	svg_legenda_box(100,	"Network", "net");
	svg_legenda_box(200,	"Sync", "sync");
	svg_legenda_box(300,	"Poll", "poll");
	svg_legenda_box(400,	"Error", "error");
	fprintf(svgfile, "</g>\n");
}