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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

void usage(char *name){
 	printf ("Usage: %s [options]\n"
		"Options: -f<pixelformat>\n"
		"            where format is one of:\n"
		"              CLUT4,CLUT8,ARGB1555,RGB565,ARGB\n"
		"         -s<width>x<heigth>\n"
		"            where width is either 720,640,360,320\n"
		"                  and height is either 288,240,480,576\n"
		"         -n\n"
		"            disables clearing the framebuffer after drawing\n"
		"            the testimage. This can be useful to keep the last\n"
		"            drawn image onscreen.\n"
		"\nExample: %s -fRGB322\n",name,name);
	exit(0);
}