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
struct snd_soc_component {int dummy; } ;
struct jz_icdc {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct jz_icdc* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void jz4725b_codec_dev_remove(struct snd_soc_component *component)
{
	struct jz_icdc *icdc = snd_soc_component_get_drvdata(component);

	clk_disable_unprepare(icdc->clk);
}