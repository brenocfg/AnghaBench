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
struct snd_soc_dai_link {scalar_t__ cpu_of_node; scalar_t__ platform_of_node; } ;

/* Variables and functions */

int asoc_simple_card_canonicalize_dailink(struct snd_soc_dai_link *dai_link)
{
	/* Assumes platform == cpu */
	if (!dai_link->platform_of_node)
		dai_link->platform_of_node = dai_link->cpu_of_node;

	return 0;
}