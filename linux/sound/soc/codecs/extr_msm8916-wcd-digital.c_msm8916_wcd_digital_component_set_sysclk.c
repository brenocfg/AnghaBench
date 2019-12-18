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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct msm8916_wcd_digital_priv {int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 struct msm8916_wcd_digital_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm8916_wcd_digital_component_set_sysclk(struct snd_soc_component *component,
						int clk_id, int source,
						unsigned int freq, int dir)
{
	struct msm8916_wcd_digital_priv *p = dev_get_drvdata(component->dev);

	return clk_set_rate(p->mclk, freq);
}