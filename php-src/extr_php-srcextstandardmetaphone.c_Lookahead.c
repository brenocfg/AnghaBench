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

__attribute__((used)) static char Lookahead(char *word, int how_far)
{
	char letter_ahead = '\0';	/* null by default */
	int idx;
	for (idx = 0; word[idx] != '\0' && idx < how_far; idx++);
	/* Edge forward in the string... */

	letter_ahead = word[idx];	/* idx will be either == to how_far or
								 * at the end of the string
								 */
	return letter_ahead;
}