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
struct wm_adsp_compr_buf {int irq_count; } ;
struct wm_adsp_compr {scalar_t__ stream; } ;
struct wm_adsp {size_t fw; int /*<<< orphan*/  pwr_lock; struct wm_adsp_compr* compr; struct wm_adsp_compr_buf* buffer; } ;
struct TYPE_2__ {scalar_t__ voice_trigger; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HOST_BUFFER_FIELD (int /*<<< orphan*/ ) ; 
 int WM_ADSP_COMPR_VOICE_TRIGGER ; 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*) ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,int) ; 
 int /*<<< orphan*/  irq_count ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_compr_fragment_elapsed (scalar_t__) ; 
 int wm_adsp_buffer_get_error (struct wm_adsp_compr_buf*) ; 
 int wm_adsp_buffer_read (struct wm_adsp_compr_buf*,int /*<<< orphan*/ ,int*) ; 
 int wm_adsp_buffer_update_avail (struct wm_adsp_compr_buf*) ; 
 TYPE_1__* wm_adsp_fw ; 

int wm_adsp_compr_handle_irq(struct wm_adsp *dsp)
{
	struct wm_adsp_compr_buf *buf;
	struct wm_adsp_compr *compr;
	int ret = 0;

	mutex_lock(&dsp->pwr_lock);

	buf = dsp->buffer;
	compr = dsp->compr;

	if (!buf) {
		ret = -ENODEV;
		goto out;
	}

	adsp_dbg(dsp, "Handling buffer IRQ\n");

	ret = wm_adsp_buffer_get_error(buf);
	if (ret < 0)
		goto out_notify; /* Wake poll to report error */

	ret = wm_adsp_buffer_read(buf, HOST_BUFFER_FIELD(irq_count),
				  &buf->irq_count);
	if (ret < 0) {
		adsp_err(dsp, "Failed to get irq_count: %d\n", ret);
		goto out;
	}

	ret = wm_adsp_buffer_update_avail(buf);
	if (ret < 0) {
		adsp_err(dsp, "Error reading avail: %d\n", ret);
		goto out;
	}

	if (wm_adsp_fw[dsp->fw].voice_trigger && buf->irq_count == 2)
		ret = WM_ADSP_COMPR_VOICE_TRIGGER;

out_notify:
	if (compr && compr->stream)
		snd_compr_fragment_elapsed(compr->stream);

out:
	mutex_unlock(&dsp->pwr_lock);

	return ret;
}