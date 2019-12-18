#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_3__* runtime; } ;
struct snd_card_asihpi_pcm {int dummy; } ;
struct snd_card_asihpi {int /*<<< orphan*/  update_interval_frames; TYPE_2__* hpi; int /*<<< orphan*/  t; struct snd_card_asihpi_pcm* llmode_streampriv; } ;
struct TYPE_6__ {scalar_t__ private_data; } ;
struct TYPE_5__ {TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADAPTER_PROPERTY_IRQ_RATE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_adapter_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_handle_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 struct snd_card_asihpi* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_card_asihpi_pcm_int_start(struct snd_pcm_substream *substream)
{
	struct snd_card_asihpi_pcm *dpcm;
	struct snd_card_asihpi *card;

	dpcm = (struct snd_card_asihpi_pcm *)substream->runtime->private_data;
	card = snd_pcm_substream_chip(substream);

	WARN_ON(in_interrupt());
	tasklet_disable(&card->t);
	card->llmode_streampriv = dpcm;
	tasklet_enable(&card->t);

	hpi_handle_error(hpi_adapter_set_property(card->hpi->adapter->index,
		HPI_ADAPTER_PROPERTY_IRQ_RATE,
		card->update_interval_frames, 0));
}