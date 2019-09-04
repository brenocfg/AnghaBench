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
struct snd_pcm_substream {int dummy; } ;
struct hdsp {int /*<<< orphan*/  lock; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ hdsp_check_for_firmware (struct hdsp*,int) ; 
 scalar_t__ hdsp_check_for_iobox (struct hdsp*) ; 
 int /*<<< orphan*/  hdsp_reset_hw_pointer (struct hdsp*) ; 
 struct hdsp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdsp_prepare(struct snd_pcm_substream *substream)
{
	struct hdsp *hdsp = snd_pcm_substream_chip(substream);
	int result = 0;

	if (hdsp_check_for_iobox (hdsp))
		return -EIO;

	if (hdsp_check_for_firmware(hdsp, 1))
		return -EIO;

	spin_lock_irq(&hdsp->lock);
	if (!hdsp->running)
		hdsp_reset_hw_pointer(hdsp);
	spin_unlock_irq(&hdsp->lock);
	return result;
}