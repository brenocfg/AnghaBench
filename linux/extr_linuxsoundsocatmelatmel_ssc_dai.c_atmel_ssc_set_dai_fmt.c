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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct platform_device {size_t id; } ;
struct atmel_ssc_info {unsigned int daifmt; } ;

/* Variables and functions */
 struct atmel_ssc_info* ssc_info ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_ssc_set_dai_fmt(struct snd_soc_dai *cpu_dai,
		unsigned int fmt)
{
	struct platform_device *pdev = to_platform_device(cpu_dai->dev);
	struct atmel_ssc_info *ssc_p = &ssc_info[pdev->id];

	ssc_p->daifmt = fmt;
	return 0;
}