#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {scalar_t__* value; } ;
struct TYPE_4__ {scalar_t__* item; } ;
struct TYPE_6__ {TYPE_2__ integer; TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;
struct rsnd_kctrl_cfg {int size; scalar_t__* val; int /*<<< orphan*/  mod; int /*<<< orphan*/  io; int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ texts; int /*<<< orphan*/  (* accept ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct rsnd_kctrl_cfg* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsnd_kctrl_put(struct snd_kcontrol *kctrl,
			  struct snd_ctl_elem_value *uc)
{
	struct rsnd_kctrl_cfg *cfg = snd_kcontrol_chip(kctrl);
	int i, change = 0;

	if (!cfg->accept(cfg->io))
		return 0;

	for (i = 0; i < cfg->size; i++) {
		if (cfg->texts) {
			change |= (uc->value.enumerated.item[i] != cfg->val[i]);
			cfg->val[i] = uc->value.enumerated.item[i];
		} else {
			change |= (uc->value.integer.value[i] != cfg->val[i]);
			cfg->val[i] = uc->value.integer.value[i];
		}
	}

	if (change && cfg->update)
		cfg->update(cfg->io, cfg->mod);

	return change;
}