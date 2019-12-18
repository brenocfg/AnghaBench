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
struct snd_ymfpci {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_ymfpci* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ymfpci_irq_wait (struct snd_ymfpci*) ; 

__attribute__((used)) static int snd_ymfpci_capture_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_ymfpci *chip = snd_pcm_substream_chip(substream);

	/* wait, until the PCI operations are not finished */
	snd_ymfpci_irq_wait(chip);
	return snd_pcm_lib_free_pages(substream);
}