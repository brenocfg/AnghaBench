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
struct rsnd_kctrl_cfg {int /*<<< orphan*/  val; } ;
struct rsnd_kctrl_cfg_m {struct rsnd_kctrl_cfg cfg; int /*<<< orphan*/  val; } ;

/* Variables and functions */

struct rsnd_kctrl_cfg *rsnd_kctrl_init_m(struct rsnd_kctrl_cfg_m *cfg)
{
	cfg->cfg.val = cfg->val;

	return &cfg->cfg;
}