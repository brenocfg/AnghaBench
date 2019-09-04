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
struct wm_adsp {size_t fw; int running; int /*<<< orphan*/  pwr_lock; scalar_t__ base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  rev; int /*<<< orphan*/  lock_regions; int /*<<< orphan*/  booted; int /*<<< orphan*/  boot_work; } ;
struct snd_soc_dapm_widget {size_t shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_caps; } ;

/* Variables and functions */
 scalar_t__ ADSP2V2_WDMA_CONFIG_2 ; 
 scalar_t__ ADSP2_CONTROL ; 
 int ADSP2_CORE_ENA ; 
 scalar_t__ ADSP2_RDMA_CONFIG_1 ; 
 int ADSP2_START ; 
 int ADSP2_SYS_ENA ; 
 scalar_t__ ADSP2_WDMA_CONFIG_1 ; 
 scalar_t__ ADSP2_WDMA_CONFIG_2 ; 
 int EIO ; 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  WM_ADSP_FW_EVENT_SHUTDOWN ; 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct wm_adsp* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int wm_adsp2_ena (struct wm_adsp*) ; 
 int /*<<< orphan*/  wm_adsp2_lock (struct wm_adsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_adsp2_show_fw_status (struct wm_adsp*) ; 
 int /*<<< orphan*/  wm_adsp2v2_show_fw_status (struct wm_adsp*) ; 
 int /*<<< orphan*/  wm_adsp_buffer_free (struct wm_adsp*) ; 
 int wm_adsp_buffer_init (struct wm_adsp*) ; 
 TYPE_1__* wm_adsp_fw ; 
 int /*<<< orphan*/  wm_adsp_signal_event_controls (struct wm_adsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_adsp_stop_watchdog (struct wm_adsp*) ; 
 int wm_coeff_sync_controls (struct wm_adsp*) ; 

int wm_adsp2_event(struct snd_soc_dapm_widget *w,
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

		ret = wm_adsp2_ena(dsp);
		if (ret != 0)
			goto err;

		/* Sync set controls */
		ret = wm_coeff_sync_controls(dsp);
		if (ret != 0)
			goto err;

		wm_adsp2_lock(dsp, dsp->lock_regions);

		ret = regmap_update_bits(dsp->regmap,
					 dsp->base + ADSP2_CONTROL,
					 ADSP2_CORE_ENA | ADSP2_START,
					 ADSP2_CORE_ENA | ADSP2_START);
		if (ret != 0)
			goto err;

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

		wm_adsp_stop_watchdog(dsp);

		/* Log firmware state, it can be useful for analysis */
		switch (dsp->rev) {
		case 0:
			wm_adsp2_show_fw_status(dsp);
			break;
		default:
			wm_adsp2v2_show_fw_status(dsp);
			break;
		}

		mutex_lock(&dsp->pwr_lock);

		dsp->running = false;

		regmap_update_bits(dsp->regmap,
				   dsp->base + ADSP2_CONTROL,
				   ADSP2_CORE_ENA | ADSP2_START, 0);

		/* Make sure DMAs are quiesced */
		switch (dsp->rev) {
		case 0:
			regmap_write(dsp->regmap,
				     dsp->base + ADSP2_RDMA_CONFIG_1, 0);
			regmap_write(dsp->regmap,
				     dsp->base + ADSP2_WDMA_CONFIG_1, 0);
			regmap_write(dsp->regmap,
				     dsp->base + ADSP2_WDMA_CONFIG_2, 0);

			regmap_update_bits(dsp->regmap,
					   dsp->base + ADSP2_CONTROL,
					   ADSP2_SYS_ENA, 0);
			break;
		default:
			regmap_write(dsp->regmap,
				     dsp->base + ADSP2_RDMA_CONFIG_1, 0);
			regmap_write(dsp->regmap,
				     dsp->base + ADSP2_WDMA_CONFIG_1, 0);
			regmap_write(dsp->regmap,
				     dsp->base + ADSP2V2_WDMA_CONFIG_2, 0);
			break;
		}

		if (wm_adsp_fw[dsp->fw].num_caps != 0)
			wm_adsp_buffer_free(dsp);

		mutex_unlock(&dsp->pwr_lock);

		adsp_dbg(dsp, "Execution stopped\n");
		break;

	default:
		break;
	}

	return 0;
err:
	regmap_update_bits(dsp->regmap, dsp->base + ADSP2_CONTROL,
			   ADSP2_SYS_ENA | ADSP2_CORE_ENA | ADSP2_START, 0);
	mutex_unlock(&dsp->pwr_lock);
	return ret;
}