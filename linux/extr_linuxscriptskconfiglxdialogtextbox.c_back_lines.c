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
 int begin_reached ; 
 char* buf ; 
 scalar_t__ end_reached ; 
 char* page ; 

__attribute__((used)) static void back_lines(int n)
{
	int i;

	begin_reached = 0;
	/* Go back 'n' lines */
	for (i = 0; i < n; i++) {
		if (*page == '\0') {
			if (end_reached) {
				end_reached = 0;
				continue;
			}
		}
		if (page == buf) {
			begin_reached = 1;
			return;
		}
		page--;
		do {
			if (page == buf) {
				begin_reached = 1;
				return;
			}
			page--;
		} while (*page != '\n');
		page++;
	}
}