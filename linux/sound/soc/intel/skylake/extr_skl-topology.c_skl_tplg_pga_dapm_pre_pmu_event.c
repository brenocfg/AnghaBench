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
struct snd_soc_dapm_widget {struct skl_module_cfg* priv; } ;
struct skl_module_cfg {TYPE_1__* pipe; } ;
struct skl_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ conn_type; } ;

/* Variables and functions */
 scalar_t__ SKL_PIPE_CONN_TYPE_FE ; 
 int skl_run_pipe (struct skl_dev*,TYPE_1__*) ; 
 int skl_tplg_bind_sinks (struct snd_soc_dapm_widget*,struct skl_dev*,struct snd_soc_dapm_widget*,struct skl_module_cfg*) ; 

__attribute__((used)) static int skl_tplg_pga_dapm_pre_pmu_event(struct snd_soc_dapm_widget *w,
							struct skl_dev *skl)
{
	struct skl_module_cfg *src_mconfig;
	int ret = 0;

	src_mconfig = w->priv;

	/*
	 * find which sink it is connected to, bind with the sink,
	 * if sink is not started, start sink pipe first, then start
	 * this pipe
	 */
	ret = skl_tplg_bind_sinks(w, skl, w, src_mconfig);
	if (ret)
		return ret;

	/* Start source pipe last after starting all sinks */
	if (src_mconfig->pipe->conn_type != SKL_PIPE_CONN_TYPE_FE)
		return skl_run_pipe(skl, src_mconfig->pipe);

	return 0;
}