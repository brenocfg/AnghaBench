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
struct samsung_spdif_info {int dummy; } ;

/* Variables and functions */
 struct samsung_spdif_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static inline struct samsung_spdif_info *to_info(struct snd_soc_dai *cpu_dai)
{
	return snd_soc_dai_get_drvdata(cpu_dai);
}