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

/* Variables and functions */
 int /*<<< orphan*/  ALLO_BOSS_CLK44EN ; 
 int /*<<< orphan*/  ALLO_BOSS_CLK48EN ; 
 int /*<<< orphan*/  ALLO_BOSS_NOCLOCK ; 
 int /*<<< orphan*/  snd_allo_boss_clk_gpio (struct snd_soc_component*) ; 
 int snd_allo_boss_is_sclk_sleep (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_allo_boss_select_clk (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool snd_allo_boss_is_master_card(struct snd_soc_component *component)
{
	bool isClk44EN, isClk48En, isNoClk;

	snd_allo_boss_clk_gpio(component);

	snd_allo_boss_select_clk(component, ALLO_BOSS_CLK44EN);
	isClk44EN = snd_allo_boss_is_sclk_sleep(component);

	snd_allo_boss_select_clk(component, ALLO_BOSS_NOCLOCK);
	isNoClk = snd_allo_boss_is_sclk_sleep(component);

	snd_allo_boss_select_clk(component, ALLO_BOSS_CLK48EN);
	isClk48En = snd_allo_boss_is_sclk_sleep(component);

	return (isClk44EN && isClk48En && !isNoClk);
}