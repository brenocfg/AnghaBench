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
struct snd_pcsp {int /*<<< orphan*/  input_dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alsa_card_pcsp_exit (struct snd_pcsp*) ; 
 int /*<<< orphan*/  pcspkr_input_remove (int /*<<< orphan*/ ) ; 
 struct snd_pcsp* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pcsp_remove(struct platform_device *dev)
{
	struct snd_pcsp *chip = platform_get_drvdata(dev);
	pcspkr_input_remove(chip->input_dev);
	alsa_card_pcsp_exit(chip);
	return 0;
}