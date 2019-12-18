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
struct snd_pmac {TYPE_2__* beep; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  buf; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BEEP_BUFLEN ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

void snd_pmac_detach_beep(struct snd_pmac *chip)
{
	if (chip->beep) {
		input_unregister_device(chip->beep->dev);
		dma_free_coherent(&chip->pdev->dev, BEEP_BUFLEN * 4,
				  chip->beep->buf, chip->beep->addr);
		kfree(chip->beep);
		chip->beep = NULL;
	}
}