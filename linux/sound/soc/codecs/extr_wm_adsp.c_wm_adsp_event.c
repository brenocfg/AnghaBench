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
struct wm_adsp {size_t fw; int running; int fatal_error; int /*<<< orphan*/  pwr_lock; TYPE_1__* ops; int /*<<< orphan*/  lock_regions; int /*<<< orphan*/  booted; int /*<<< orphan*/  boot_work; } ;
struct snd_soc_dapm_widget {size_t shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_caps; } ;
struct TYPE_3__ {int (* enable_core ) (struct wm_adsp*) ;int (* lock_memory ) (struct wm_adsp*,int /*<<< orphan*/ ) ;int (* start_core ) (struct wm_adsp*) ;int /*<<< orphan*/  (* disable_core ) (struct wm_adsp*) ;int /*<<< orphan*/  (* stop_core ) (struct wm_adsp*) ;int /*<<< orphan*/  (* show_fw_status ) (struct wm_adsp*) ;int /*<<< orphan*/  (* stop_watchdog ) (struct wm_adsp*) ;} ;

/* Variables and functions */
 int EIO ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  WM_ADSP_FW_EVENT_SHUTDOWN ; 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*) ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct wm_adsp* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int stub1 (struct wm_adsp*) ; 
 int stub2 (struct wm_adsp*,int /*<<< orphan*/ ) ; 
 int stub3 (struct wm_adsp*) ; 
 int /*<<< orphan*/  stub4 (struct wm_adsp*) ; 
 int /*<<< orphan*/  stub5 (struct wm_adsp*) ; 
 int /*<<< orphan*/  stub6 (struct wm_adsp*) ; 
 int /*<<< orphan*/  stub7 (struct wm_adsp*) ; 
 int /*<<< orphan*/  stub8 (struct wm_adsp*) ; 
 int /*<<< orphan*/  stub9 (struct wm_adsp*) ; 
 int /*<<< orphan*/  wm_adsp_buffer_free (struct wm_adsp*) ; 
 int wm_adsp_buffer_init (struct wm_adsp*) ; 
 TYPE_2__* wm_adsp_fw ; 
 int /*<<< orphan*/  wm_adsp_signal_event_controls (struct wm_adsp*,int /*<<< orphan*/ ) ; 
 int wm_coeff_sync_controls (struct wm_adsp*) ; 

int wm_adsp_event(struct snd_soc_dapm_widget *w,
		  struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm_adsp *dsps = snd_soc_component_get_drvdata(component);
	struct wm_adsp *dsp = &dsps[w->shift];
	int ret;

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		flush_work(&dsp->boot_work);

		mutex_lock(&dsp->pwr_lock);

		if (!dsp->booted) {
			ret = -EIO;
			goto err;
		}

		if (dsp->ops->enable_core) {
			ret = dsp->ops->enable_core(dsp);
			if (ret != 0)
				goto err;
		}

		/* Sync set controls */
		ret = wm_coeff_sync_controls(dsp);
		if (ret != 0)
			goto err;

		if (dsp->ops->lock_memory) {
			ret = dsp->ops->lock_memory(dsp, dsp->lock_regions);
			if (ret != 0) {
				adsp_err(dsp, "Error configuring MPU: %d\n",
					 ret);
				goto err;
			}
		}

		if (dsp->ops->start_core) {
			ret = dsp->ops->start_core(dsp);
			if (ret != 0)
				goto err;
		}

		if (wm_adsp_fw[dsp->fw].num_caps != 0) {
			ret = wm_adsp_buffer_init(dsp);
			if (ret < 0)
				goto err;
		}

		dsp->running = true;

		mutex_unlock(&dsp->pwr_lock);
		break;

	case SND_SOC_DAPM_PRE_PMD:
		/* Tell the firmware to cleanup */
		wm_adsp_signal_event_controls(dsp, WM_ADSP_FW_EVENT_SHUTDOWN);

		if (dsp->ops->stop_watchdog)
			dsp->ops->stop_watchdog(dsp);

		/* Log firmware state, it can be useful for analysis */
		if (dsp->ops->show_fw_status)
			dsp->ops->show_fw_status(dsp);

		mutex_lock(&dsp->pwr_lock);

		dsp->running = false;

		if (dsp->ops->stop_core)
			dsp->ops->stop_core(dsp);
		if (dsp->ops->disable_core)
			dsp->ops->disable_core(dsp);

		if (wm_adsp_fw[dsp->fw].num_caps != 0)
			wm_adsp_buffer_free(dsp);

		dsp->fatal_error = false;

		mutex_unlock(&dsp->pwr_lock);

		adsp_dbg(dsp, "Execution stopped\n");
		break;

	default:
		break;
	}

	return 0;
err:
	if (dsp->ops->stop_core)
		dsp->ops->stop_core(dsp);
	if (dsp->ops->disable_core)
		dsp->ops->disable_core(dsp);
	mutex_unlock(&dsp->pwr_lock);
	return ret;
}