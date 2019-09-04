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
struct wm_adsp_compr {struct snd_compr_stream* stream; struct wm_adsp* dsp; } ;
struct wm_adsp {size_t fw; int /*<<< orphan*/  pwr_lock; struct wm_adsp_compr* compr; } ;
struct snd_compr_stream {scalar_t__ direction; TYPE_1__* runtime; } ;
struct TYPE_4__ {scalar_t__ num_caps; scalar_t__ compr_direction; } ;
struct TYPE_3__ {struct wm_adsp_compr* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*) ; 
 struct wm_adsp_compr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* wm_adsp_fw ; 

int wm_adsp_compr_open(struct wm_adsp *dsp, struct snd_compr_stream *stream)
{
	struct wm_adsp_compr *compr;
	int ret = 0;

	mutex_lock(&dsp->pwr_lock);

	if (wm_adsp_fw[dsp->fw].num_caps == 0) {
		adsp_err(dsp, "Firmware does not support compressed API\n");
		ret = -ENXIO;
		goto out;
	}

	if (wm_adsp_fw[dsp->fw].compr_direction != stream->direction) {
		adsp_err(dsp, "Firmware does not support stream direction\n");
		ret = -EINVAL;
		goto out;
	}

	if (dsp->compr) {
		/* It is expect this limitation will be removed in future */
		adsp_err(dsp, "Only a single stream supported per DSP\n");
		ret = -EBUSY;
		goto out;
	}

	compr = kzalloc(sizeof(*compr), GFP_KERNEL);
	if (!compr) {
		ret = -ENOMEM;
		goto out;
	}

	compr->dsp = dsp;
	compr->stream = stream;

	dsp->compr = compr;

	stream->runtime->private_data = compr;

out:
	mutex_unlock(&dsp->pwr_lock);

	return ret;
}