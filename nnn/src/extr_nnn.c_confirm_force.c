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
 int get_input (char*) ; 
 int nselected ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char confirm_force(bool selection)
{
	char str[64] = "forcibly remove current file (unrecoverable)? [y/Y confirms]";
	int r;

	if (selection)
		snprintf(str, 64, "forcibly remove %d file(s) (unrecoverable)? [y/Y confirms]", nselected);

	r = get_input(str);

	if (r == 'y' || r == 'Y')
		return 'f'; /* forceful */
	return 'i'; /* interactive */
}