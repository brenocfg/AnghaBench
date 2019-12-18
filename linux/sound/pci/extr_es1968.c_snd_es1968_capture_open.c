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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_6__ {scalar_t__ period_bytes_max; scalar_t__ buffer_bytes_max; } ;
struct snd_pcm_runtime {TYPE_3__ hw; struct esschan* private_data; } ;
struct esschan {int* apu; int /*<<< orphan*/  list; TYPE_2__* mixbuf; int /*<<< orphan*/  mode; struct snd_pcm_substream* substream; scalar_t__ running; scalar_t__* apu_mode; } ;
struct es1968 {int /*<<< orphan*/  substream_lock; int /*<<< orphan*/  substream_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  area; } ;
struct TYPE_5__ {TYPE_1__ buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ESM_APU_PCM_CAPTURE ; 
 int /*<<< orphan*/  ESM_APU_PCM_RATECONV ; 
 int /*<<< orphan*/  ESM_MIXBUF_SIZE ; 
 int /*<<< orphan*/  ESM_MODE_CAPTURE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 scalar_t__ calc_available_memory_size (struct es1968*) ; 
 int /*<<< orphan*/  kfree (struct esschan*) ; 
 struct esschan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_es1968_alloc_apu_pair (struct es1968*,int /*<<< orphan*/ ) ; 
 TYPE_3__ snd_es1968_capture ; 
 int /*<<< orphan*/  snd_es1968_free_apu_pair (struct es1968*,int) ; 
 TYPE_2__* snd_es1968_new_memory (struct es1968*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_pow2 (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct es1968* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_es1968_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct es1968 *chip = snd_pcm_substream_chip(substream);
	struct esschan *es;
	int apu1, apu2;

	apu1 = snd_es1968_alloc_apu_pair(chip, ESM_APU_PCM_CAPTURE);
	if (apu1 < 0)
		return apu1;
	apu2 = snd_es1968_alloc_apu_pair(chip, ESM_APU_PCM_RATECONV);
	if (apu2 < 0) {
		snd_es1968_free_apu_pair(chip, apu1);
		return apu2;
	}
	
	es = kzalloc(sizeof(*es), GFP_KERNEL);
	if (!es) {
		snd_es1968_free_apu_pair(chip, apu1);
		snd_es1968_free_apu_pair(chip, apu2);
		return -ENOMEM;
	}

	es->apu[0] = apu1;
	es->apu[1] = apu1 + 1;
	es->apu[2] = apu2;
	es->apu[3] = apu2 + 1;
	es->apu_mode[0] = 0;
	es->apu_mode[1] = 0;
	es->apu_mode[2] = 0;
	es->apu_mode[3] = 0;
	es->running = 0;
	es->substream = substream;
	es->mode = ESM_MODE_CAPTURE;

	/* get mixbuffer */
	if ((es->mixbuf = snd_es1968_new_memory(chip, ESM_MIXBUF_SIZE)) == NULL) {
		snd_es1968_free_apu_pair(chip, apu1);
		snd_es1968_free_apu_pair(chip, apu2);
		kfree(es);
                return -ENOMEM;
        }
	memset(es->mixbuf->buf.area, 0, ESM_MIXBUF_SIZE);

	runtime->private_data = es;
	runtime->hw = snd_es1968_capture;
	runtime->hw.buffer_bytes_max = runtime->hw.period_bytes_max =
		calc_available_memory_size(chip) - 1024; /* keep MIXBUF size */
	snd_pcm_hw_constraint_pow2(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES);

	spin_lock_irq(&chip->substream_lock);
	list_add(&es->list, &chip->substream_list);
	spin_unlock_irq(&chip->substream_lock);

	return 0;
}