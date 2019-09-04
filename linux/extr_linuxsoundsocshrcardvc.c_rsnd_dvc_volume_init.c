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
typedef  int u32 ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dvc {int /*<<< orphan*/  ren; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVC_ADINR ; 
 int /*<<< orphan*/  DVC_DVUCR ; 
 int /*<<< orphan*/  DVC_DVUIR ; 
 int /*<<< orphan*/  DVC_VRCTR ; 
 int /*<<< orphan*/  DVC_VRDBR ; 
 int /*<<< orphan*/  DVC_VRPDR ; 
 int rsnd_dvc_get_vrdbr (struct rsnd_dvc*) ; 
 int rsnd_dvc_get_vrpdr (struct rsnd_dvc*) ; 
 int /*<<< orphan*/  rsnd_dvc_volume_parameter (struct rsnd_dai_stream*,struct rsnd_mod*) ; 
 int rsnd_get_adinr_bit (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 scalar_t__ rsnd_kctrl_vals (int /*<<< orphan*/ ) ; 
 struct rsnd_dvc* rsnd_mod_to_dvc (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 int rsnd_runtime_channel_after_ctu (struct rsnd_dai_stream*) ; 

__attribute__((used)) static void rsnd_dvc_volume_init(struct rsnd_dai_stream *io,
				 struct rsnd_mod *mod)
{
	struct rsnd_dvc *dvc = rsnd_mod_to_dvc(mod);
	u32 adinr = 0;
	u32 dvucr = 0;
	u32 vrctr = 0;
	u32 vrpdr = 0;
	u32 vrdbr = 0;

	adinr = rsnd_get_adinr_bit(mod, io) |
		rsnd_runtime_channel_after_ctu(io);

	/* Enable Digital Volume, Zero Cross Mute Mode */
	dvucr |= 0x101;

	/* Enable Ramp */
	if (rsnd_kctrl_vals(dvc->ren)) {
		dvucr |= 0x10;

		/*
		 * FIXME !!
		 * use scale-downed Digital Volume
		 * as Volume Ramp
		 * 7F FFFF -> 3FF
		 */
		vrctr = 0xff;
		vrpdr = rsnd_dvc_get_vrpdr(dvc);
		vrdbr = rsnd_dvc_get_vrdbr(dvc);
	}

	/* Initialize operation */
	rsnd_mod_write(mod, DVC_DVUIR, 1);

	/* General Information */
	rsnd_mod_write(mod, DVC_ADINR, adinr);
	rsnd_mod_write(mod, DVC_DVUCR, dvucr);

	/* Volume Ramp Parameter */
	rsnd_mod_write(mod, DVC_VRCTR, vrctr);
	rsnd_mod_write(mod, DVC_VRPDR, vrpdr);
	rsnd_mod_write(mod, DVC_VRDBR, vrdbr);

	/* Digital Volume Function Parameter */
	rsnd_dvc_volume_parameter(io, mod);

	/* cancel operation */
	rsnd_mod_write(mod, DVC_DVUIR, 0);
}