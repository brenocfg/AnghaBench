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
struct snd_soc_dapm_path {TYPE_1__* source; TYPE_2__* sink; scalar_t__ is_supply; scalar_t__ weak; } ;
struct TYPE_4__ {scalar_t__* endpoints; } ;
struct TYPE_3__ {scalar_t__* endpoints; } ;

/* Variables and functions */
 size_t SND_SOC_DAPM_DIR_IN ; 
 size_t SND_SOC_DAPM_DIR_OUT ; 
 int /*<<< orphan*/  dapm_widget_invalidate_input_paths (TYPE_2__*) ; 
 int /*<<< orphan*/  dapm_widget_invalidate_output_paths (TYPE_1__*) ; 

__attribute__((used)) static void dapm_path_invalidate(struct snd_soc_dapm_path *p)
{
	/*
	 * Weak paths or supply paths do not influence the number of input or
	 * output paths of their neighbors.
	 */
	if (p->weak || p->is_supply)
		return;

	/*
	 * The number of connected endpoints is the sum of the number of
	 * connected endpoints of all neighbors. If a node with 0 connected
	 * endpoints is either connected or disconnected that sum won't change,
	 * so there is no need to re-check the path.
	 */
	if (p->source->endpoints[SND_SOC_DAPM_DIR_IN] != 0)
		dapm_widget_invalidate_input_paths(p->sink);
	if (p->sink->endpoints[SND_SOC_DAPM_DIR_OUT] != 0)
		dapm_widget_invalidate_output_paths(p->source);
}