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
struct wm_adsp_compr {int /*<<< orphan*/  buf; struct wm_adsp* dsp; } ;
struct wm_adsp {int /*<<< orphan*/  pwr_lock; } ;
struct snd_compr_stream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct wm_adsp_compr* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HOST_BUFFER_FIELD (int /*<<< orphan*/ ) ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  compr_dbg (struct wm_adsp_compr*,char*,int) ; 
 int /*<<< orphan*/  compr_err (struct wm_adsp_compr*,char*,int) ; 
 int /*<<< orphan*/  high_water_mark ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm_adsp_buffer_clear (int /*<<< orphan*/ ) ; 
 int wm_adsp_buffer_get_error (int /*<<< orphan*/ ) ; 
 int wm_adsp_buffer_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wm_adsp_compr_attach (struct wm_adsp_compr*) ; 
 int /*<<< orphan*/  wm_adsp_compr_attached (struct wm_adsp_compr*) ; 
 int /*<<< orphan*/  wm_adsp_compr_frag_words (struct wm_adsp_compr*) ; 

int wm_adsp_compr_trigger(struct snd_compr_stream *stream, int cmd)
{
	struct wm_adsp_compr *compr = stream->runtime->private_data;
	struct wm_adsp *dsp = compr->dsp;
	int ret = 0;

	compr_dbg(compr, "Trigger: %d\n", cmd);

	mutex_lock(&dsp->pwr_lock);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (!wm_adsp_compr_attached(compr)) {
			ret = wm_adsp_compr_attach(compr);
			if (ret < 0) {
				compr_err(compr, "Failed to link buffer and stream: %d\n",
					  ret);
				break;
			}
		}

		ret = wm_adsp_buffer_get_error(compr->buf);
		if (ret < 0)
			break;

		/* Trigger the IRQ at one fragment of data */
		ret = wm_adsp_buffer_write(compr->buf,
					   HOST_BUFFER_FIELD(high_water_mark),
					   wm_adsp_compr_frag_words(compr));
		if (ret < 0) {
			compr_err(compr, "Failed to set high water mark: %d\n",
				  ret);
			break;
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		if (wm_adsp_compr_attached(compr))
			wm_adsp_buffer_clear(compr->buf);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&dsp->pwr_lock);

	return ret;
}