#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_link {scalar_t__ num_platforms; TYPE_2__* platforms; TYPE_1__* cpus; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;
struct TYPE_3__ {scalar_t__ of_node; } ;

/* Variables and functions */

void asoc_simple_canonicalize_platform(struct snd_soc_dai_link *dai_link)
{
	/* Assumes platform == cpu */
	if (!dai_link->platforms->of_node)
		dai_link->platforms->of_node = dai_link->cpus->of_node;

	/*
	 * DPCM BE can be no platform.
	 * Alloced memory will be waste, but not leak.
	 */
	if (!dai_link->platforms->of_node)
		dai_link->num_platforms = 0;
}