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
typedef  enum snd_ff_clock_src { ____Placeholder_snd_ff_clock_src } snd_ff_clock_src ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 

const char *snd_ff_proc_get_clk_label(enum snd_ff_clock_src src)
{
	static const char *const labels[] = {
		"Internal",
		"S/PDIF",
		"ADAT1",
		"ADAT2",
		"Word",
		"LTC",
	};

	if (src >= ARRAY_SIZE(labels))
		return NULL;

	return labels[src];
}