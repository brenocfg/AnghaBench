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
struct snd_pcm_substream {int /*<<< orphan*/  dma_buffer; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct imx_pcm_runtime_data* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct imx_pcm_runtime_data {int poll_time_ns; scalar_t__ offset; int /*<<< orphan*/  period; int /*<<< orphan*/  periods; } ;

/* Variables and functions */
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int params_period_size (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_periods (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_imx_pcm_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct imx_pcm_runtime_data *iprtd = runtime->private_data;

	iprtd->periods = params_periods(params);
	iprtd->period = params_period_bytes(params);
	iprtd->offset = 0;
	iprtd->poll_time_ns = 1000000000 / params_rate(params) *
				params_period_size(params);
	snd_pcm_set_runtime_buffer(substream, &substream->dma_buffer);

	return 0;
}