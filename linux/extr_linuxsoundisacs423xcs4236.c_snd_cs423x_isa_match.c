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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNDRV_AUTO_DMA ; 
 scalar_t__ SNDRV_AUTO_IRQ ; 
 scalar_t__ SNDRV_AUTO_PORT ; 
 scalar_t__* cport ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__* dma1 ; 
 int /*<<< orphan*/ * enable ; 
 scalar_t__* irq ; 
 scalar_t__ is_isapnp_selected (unsigned int) ; 
 scalar_t__* port ; 

__attribute__((used)) static int snd_cs423x_isa_match(struct device *pdev,
				unsigned int dev)
{
	if (!enable[dev] || is_isapnp_selected(dev))
		return 0;

	if (port[dev] == SNDRV_AUTO_PORT) {
		dev_err(pdev, "please specify port\n");
		return 0;
	}
	if (cport[dev] == SNDRV_AUTO_PORT) {
		dev_err(pdev, "please specify cport\n");
		return 0;
	}
	if (irq[dev] == SNDRV_AUTO_IRQ) {
		dev_err(pdev, "please specify irq\n");
		return 0;
	}
	if (dma1[dev] == SNDRV_AUTO_DMA) {
		dev_err(pdev, "please specify dma1\n");
		return 0;
	}
	return 1;
}