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
typedef  int /*<<< orphan*/  u32 ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dvc {int /*<<< orphan*/  volume; int /*<<< orphan*/  ren; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVC_VOL0R ; 
 int /*<<< orphan*/  DVC_VOL1R ; 
 int /*<<< orphan*/  DVC_VOL2R ; 
 int /*<<< orphan*/  DVC_VOL3R ; 
 int /*<<< orphan*/  DVC_VOL4R ; 
 int /*<<< orphan*/  DVC_VOL5R ; 
 int /*<<< orphan*/  DVC_VOL6R ; 
 int /*<<< orphan*/  DVC_VOL7R ; 
 int RSND_MAX_CHANNELS ; 
 int /*<<< orphan*/  rsnd_kctrl_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_kctrl_valm (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rsnd_kctrl_vals (int /*<<< orphan*/ ) ; 
 struct rsnd_dvc* rsnd_mod_to_dvc (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsnd_dvc_volume_parameter(struct rsnd_dai_stream *io,
					      struct rsnd_mod *mod)
{
	struct rsnd_dvc *dvc = rsnd_mod_to_dvc(mod);
	u32 val[RSND_MAX_CHANNELS];
	int i;

	/* Enable Ramp */
	if (rsnd_kctrl_vals(dvc->ren))
		for (i = 0; i < RSND_MAX_CHANNELS; i++)
			val[i] = rsnd_kctrl_max(dvc->volume);
	else
		for (i = 0; i < RSND_MAX_CHANNELS; i++)
			val[i] = rsnd_kctrl_valm(dvc->volume, i);

	/* Enable Digital Volume */
	rsnd_mod_write(mod, DVC_VOL0R, val[0]);
	rsnd_mod_write(mod, DVC_VOL1R, val[1]);
	rsnd_mod_write(mod, DVC_VOL2R, val[2]);
	rsnd_mod_write(mod, DVC_VOL3R, val[3]);
	rsnd_mod_write(mod, DVC_VOL4R, val[4]);
	rsnd_mod_write(mod, DVC_VOL5R, val[5]);
	rsnd_mod_write(mod, DVC_VOL6R, val[6]);
	rsnd_mod_write(mod, DVC_VOL7R, val[7]);
}