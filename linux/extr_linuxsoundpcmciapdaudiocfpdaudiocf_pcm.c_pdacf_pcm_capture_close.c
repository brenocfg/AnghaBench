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
struct snd_pdacf {int /*<<< orphan*/ * pcm_substream; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pdacf_reinit (struct snd_pdacf*,int /*<<< orphan*/ ) ; 
 struct snd_pdacf* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pdacf_pcm_capture_close(struct snd_pcm_substream *subs)
{
	struct snd_pdacf *chip = snd_pcm_substream_chip(subs);

	if (!chip)
		return -EINVAL;
	pdacf_reinit(chip, 0);
	chip->pcm_substream = NULL;
	return 0;
}