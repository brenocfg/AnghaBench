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
struct snd_pcm_substream {int dummy; } ;
struct snd_card_asihpi {int /*<<< orphan*/  t; int /*<<< orphan*/ * llmode_streampriv; TYPE_2__* hpi; } ;
struct TYPE_4__ {TYPE_1__* adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADAPTER_PROPERTY_IRQ_RATE ; 
 int /*<<< orphan*/  hpi_adapter_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_handle_error (int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 struct snd_card_asihpi* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_card_asihpi_pcm_int_stop(struct snd_pcm_substream *substream)
{
	struct snd_card_asihpi *card;

	card = snd_pcm_substream_chip(substream);

	hpi_handle_error(hpi_adapter_set_property(card->hpi->adapter->index,
		HPI_ADAPTER_PROPERTY_IRQ_RATE, 0, 0));

	if (in_interrupt())
		card->llmode_streampriv = NULL;
	else {
		tasklet_disable(&card->t);
		card->llmode_streampriv = NULL;
		tasklet_enable(&card->t);
	}
}