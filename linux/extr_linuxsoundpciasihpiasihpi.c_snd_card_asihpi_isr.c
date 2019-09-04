#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_card_asihpi {int /*<<< orphan*/  t; } ;
struct hpi_adapter {TYPE_1__* snd_card; } ;
struct TYPE_2__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_card_asihpi_isr(struct hpi_adapter *a)
{
	struct snd_card_asihpi *asihpi;

	WARN_ON(!a || !a->snd_card || !a->snd_card->private_data);
	asihpi = (struct snd_card_asihpi *)a->snd_card->private_data;
	tasklet_schedule(&asihpi->t);
}