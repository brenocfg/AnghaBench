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

__attribute__((used)) static unsigned int find_best_div(unsigned int in,
	unsigned int max, unsigned int div)
{
	unsigned int d;

	if (in <= max)
		return 1;

	d = in / max;
	if (in % max)
		d++;

	while (div % d != 0)
		d++;


	return d;
}