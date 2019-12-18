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
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  COLOR_BLUE ; 
 int /*<<< orphan*/  COLOR_CYAN ; 
 int /*<<< orphan*/  COLOR_GREEN ; 
 int /*<<< orphan*/  COLOR_MAGENTA ; 
 int /*<<< orphan*/  COLOR_RED ; 
 int /*<<< orphan*/  COLOR_WHITE ; 
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int /*<<< orphan*/  foregroundColor ; 
 scalar_t__ strcmp (char*,char*) ; 

void nmstermio_set_foregroundcolor(char *c) {

	if(strcmp("white", c) == 0)
		foregroundColor =  COLOR_WHITE;
	else if(strcmp("yellow", c) == 0)
		foregroundColor = COLOR_YELLOW;
	else if(strcmp("black", c) == 0)
		foregroundColor = COLOR_BLACK;
	else if(strcmp("magenta", c) == 0)
		foregroundColor = COLOR_MAGENTA;
	else if(strcmp("blue", c) == 0)
		foregroundColor = COLOR_BLUE;
	else if(strcmp("green", c) == 0)
		foregroundColor = COLOR_GREEN;
	else if(strcmp("red", c) == 0)
		foregroundColor = COLOR_RED;
	else if(strcmp("cyan", c) == 0)
		foregroundColor = COLOR_CYAN;
	else
		foregroundColor = COLOR_BLUE;
}