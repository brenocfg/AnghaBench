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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpc5200_audio_dma_destroy (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psc_ac97_of_remove(struct platform_device *op)
{
	mpc5200_audio_dma_destroy(op);
	snd_soc_unregister_component(&op->dev);
	snd_soc_set_ac97_ops(NULL);
	return 0;
}