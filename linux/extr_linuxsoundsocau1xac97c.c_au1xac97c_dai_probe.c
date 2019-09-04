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
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ ac97c_workdata ; 

__attribute__((used)) static int au1xac97c_dai_probe(struct snd_soc_dai *dai)
{
	return ac97c_workdata ? 0 : -ENODEV;
}