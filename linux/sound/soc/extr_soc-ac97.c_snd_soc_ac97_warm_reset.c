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
struct snd_ac97 {int dummy; } ;
struct pinctrl {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pstate_run; int /*<<< orphan*/  gpio_sync; int /*<<< orphan*/  pstate_warm_reset; struct pinctrl* pctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pinctrl_select_state (struct pinctrl*,int /*<<< orphan*/ ) ; 
 TYPE_1__ snd_ac97_rst_cfg ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_soc_ac97_warm_reset(struct snd_ac97 *ac97)
{
	struct pinctrl *pctl = snd_ac97_rst_cfg.pctl;

	pinctrl_select_state(pctl, snd_ac97_rst_cfg.pstate_warm_reset);

	gpio_direction_output(snd_ac97_rst_cfg.gpio_sync, 1);

	udelay(10);

	gpio_direction_output(snd_ac97_rst_cfg.gpio_sync, 0);

	pinctrl_select_state(pctl, snd_ac97_rst_cfg.pstate_run);
	msleep(2);
}