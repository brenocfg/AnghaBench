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
struct wm_adsp_compr {struct wm_adsp_compr* raw_buf; int /*<<< orphan*/  list; struct wm_adsp* dsp; } ;
struct wm_adsp {int /*<<< orphan*/  pwr_lock; } ;
struct snd_compr_stream {TYPE_1__* runtime; } ;
struct TYPE_2__ {struct wm_adsp_compr* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wm_adsp_compr*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm_adsp_compr_detach (struct wm_adsp_compr*) ; 

int wm_adsp_compr_free(struct snd_compr_stream *stream)
{
	struct wm_adsp_compr *compr = stream->runtime->private_data;
	struct wm_adsp *dsp = compr->dsp;

	mutex_lock(&dsp->pwr_lock);

	wm_adsp_compr_detach(compr);
	list_del(&compr->list);

	kfree(compr->raw_buf);
	kfree(compr);

	mutex_unlock(&dsp->pwr_lock);

	return 0;
}