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
struct sof_ipc_comp_config {int /*<<< orphan*/  frame_fmt; int /*<<< orphan*/  periods_source; int /*<<< orphan*/  periods_sink; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_sof_dev* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void sof_dbg_comp_config(struct snd_soc_component *scomp,
				struct sof_ipc_comp_config *config)
{
	struct snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);

	dev_dbg(sdev->dev, " config: periods snk %d src %d fmt %d\n",
		config->periods_sink, config->periods_source,
		config->frame_fmt);
}