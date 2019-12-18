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
struct nm256 {scalar_t__ irq; struct nm256* ac97_regs; int /*<<< orphan*/  pci; int /*<<< orphan*/  res_buffer; int /*<<< orphan*/  res_cport; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cport; TYPE_1__* streams; } ;
struct TYPE_2__ {scalar_t__ running; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct nm256*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nm256*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_nm256_capture_stop (struct nm256*) ; 
 int /*<<< orphan*/  snd_nm256_playback_stop (struct nm256*) ; 

__attribute__((used)) static int snd_nm256_free(struct nm256 *chip)
{
	if (chip->streams[SNDRV_PCM_STREAM_PLAYBACK].running)
		snd_nm256_playback_stop(chip);
	if (chip->streams[SNDRV_PCM_STREAM_CAPTURE].running)
		snd_nm256_capture_stop(chip);

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

	iounmap(chip->cport);
	iounmap(chip->buffer);
	release_and_free_resource(chip->res_cport);
	release_and_free_resource(chip->res_buffer);

	pci_disable_device(chip->pci);
	kfree(chip->ac97_regs);
	kfree(chip);
	return 0;
}