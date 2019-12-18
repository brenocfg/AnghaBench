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
struct snd_card_asihpi {TYPE_2__* llmode_streampriv; } ;
struct hpi_adapter {TYPE_1__* snd_card; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;
struct TYPE_3__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  snd_card_asihpi_timer_function (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_card_asihpi_int_task(unsigned long data)
{
	struct hpi_adapter *a = (struct hpi_adapter *)data;
	struct snd_card_asihpi *asihpi;

	WARN_ON(!a || !a->snd_card || !a->snd_card->private_data);
	asihpi = (struct snd_card_asihpi *)a->snd_card->private_data;
	if (asihpi->llmode_streampriv)
		snd_card_asihpi_timer_function(
			&asihpi->llmode_streampriv->timer);
}