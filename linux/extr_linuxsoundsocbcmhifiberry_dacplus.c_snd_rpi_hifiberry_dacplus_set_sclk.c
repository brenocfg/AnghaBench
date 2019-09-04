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
struct pcm512x_priv {int /*<<< orphan*/  sclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_44EN_RATE ; 
 int /*<<< orphan*/  CLK_48EN_RATE ; 
 int HIFIBERRY_DACPRO_CLK44EN ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_rpi_hifiberry_dacplus_clk_for_rate (int) ; 
 int /*<<< orphan*/  snd_rpi_hifiberry_dacplus_select_clk (struct snd_soc_component*,int) ; 
 struct pcm512x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void snd_rpi_hifiberry_dacplus_set_sclk(struct snd_soc_component *component,
	int sample_rate)
{
	struct pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);

	if (!IS_ERR(pcm512x->sclk)) {
		int ctype;

		ctype = snd_rpi_hifiberry_dacplus_clk_for_rate(sample_rate);
		clk_set_rate(pcm512x->sclk, (ctype == HIFIBERRY_DACPRO_CLK44EN)
			? CLK_44EN_RATE : CLK_48EN_RATE);
		snd_rpi_hifiberry_dacplus_select_clk(component, ctype);
	}
}