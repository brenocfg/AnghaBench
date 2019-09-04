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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_2__ {int rate_min; int rate_max; int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct rme96 {int /*<<< orphan*/  lock; struct snd_pcm_substream* capture_substream; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 scalar_t__ RME96_INPUT_ANALOG ; 
 int /*<<< orphan*/  rme96_set_buffer_size_constraint (struct rme96*,struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_rate_to_rate_bit (int) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct rme96* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int snd_rme96_capture_getrate (struct rme96*,int*) ; 
 TYPE_1__ snd_rme96_capture_spdif_info ; 
 scalar_t__ snd_rme96_getinputtype (struct rme96*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_rme96_capture_spdif_open(struct snd_pcm_substream *substream)
{
        int isadat, rate;
	struct rme96 *rme96 = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	snd_pcm_set_sync(substream);
	runtime->hw = snd_rme96_capture_spdif_info;
        if (snd_rme96_getinputtype(rme96) != RME96_INPUT_ANALOG &&
            (rate = snd_rme96_capture_getrate(rme96, &isadat)) > 0)
        {
                if (isadat) {
                        return -EIO;
                }
                runtime->hw.rates = snd_pcm_rate_to_rate_bit(rate);
                runtime->hw.rate_min = rate;
                runtime->hw.rate_max = rate;
        }
        
	spin_lock_irq(&rme96->lock);
	if (rme96->capture_substream) {
		spin_unlock_irq(&rme96->lock);
                return -EBUSY;
        }
	rme96->capture_substream = substream;
	spin_unlock_irq(&rme96->lock);
	
	rme96_set_buffer_size_constraint(rme96, runtime);
	return 0;
}