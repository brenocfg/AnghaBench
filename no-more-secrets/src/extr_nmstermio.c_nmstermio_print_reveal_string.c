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
 int /*<<< orphan*/  BOLD () ; 
 int /*<<< orphan*/  CLEAR_ATTR () ; 
 int /*<<< orphan*/  FOREGROUND_COLOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foregroundColor ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void nmstermio_print_reveal_string(char *s, int colorOn) {
	
	// Set bold and foreground color
	BOLD();
	if (colorOn) {
		FOREGROUND_COLOR(foregroundColor);
	}
	
	// print string
	printf("%s", s);
	
	// Unset bold and foreground color
	CLEAR_ATTR();
}