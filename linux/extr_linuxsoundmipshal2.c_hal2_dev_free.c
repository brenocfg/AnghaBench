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
struct snd_hal2 {int dummy; } ;
struct snd_device {struct snd_hal2* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGI_HPCDMA_IRQ ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct snd_hal2*) ; 
 int /*<<< orphan*/  kfree (struct snd_hal2*) ; 

__attribute__((used)) static int hal2_dev_free(struct snd_device *device)
{
	struct snd_hal2 *hal2 = device->device_data;

	free_irq(SGI_HPCDMA_IRQ, hal2);
	kfree(hal2);
	return 0;
}