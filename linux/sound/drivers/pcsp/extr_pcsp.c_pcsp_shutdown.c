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
struct snd_pcsp {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcsp_stop_beep (struct snd_pcsp*) ; 
 struct snd_pcsp* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void pcsp_shutdown(struct platform_device *dev)
{
	struct snd_pcsp *chip = platform_get_drvdata(dev);
	pcsp_stop_beep(chip);
}