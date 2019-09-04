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
struct sst_pdata {struct sst_hsw* dsp; } ;
struct sst_hsw {int dummy; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  SST_HSW_DEVICE_CLOCK_MASTER ; 
 int /*<<< orphan*/  SST_HSW_DEVICE_MCLK_FREQ_24_MHZ ; 
 int /*<<< orphan*/  SST_HSW_DEVICE_SSP_0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sst_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int sst_hsw_device_set_config (struct sst_hsw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int haswell_rtd_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct sst_pdata *pdata = dev_get_platdata(component->dev);
	struct sst_hsw *haswell = pdata->dsp;
	int ret;

	/* Set ADSP SSP port settings */
	ret = sst_hsw_device_set_config(haswell, SST_HSW_DEVICE_SSP_0,
		SST_HSW_DEVICE_MCLK_FREQ_24_MHZ,
		SST_HSW_DEVICE_CLOCK_MASTER, 9);
	if (ret < 0) {
		dev_err(rtd->dev, "failed to set device config\n");
		return ret;
	}

	return 0;
}