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
struct rsnd_dvc {int /*<<< orphan*/  ren; int /*<<< orphan*/  mute; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVC_DVUER ; 
 int /*<<< orphan*/  DVC_VRDBR ; 
 int /*<<< orphan*/  DVC_VRPDR ; 
 int /*<<< orphan*/  DVC_ZCMCR ; 
 int rsnd_dvc_get_vrdbr (struct rsnd_dvc*) ; 
 int rsnd_dvc_get_vrpdr (struct rsnd_dvc*) ; 
 int /*<<< orphan*/  rsnd_dvc_volume_parameter (struct rsnd_dai_stream*,struct rsnd_mod*) ; 
 int rsnd_kctrl_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_kctrl_valm (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rsnd_kctrl_vals (int /*<<< orphan*/ ) ; 
 struct rsnd_dvc* rsnd_mod_to_dvc (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rsnd_dvc_volume_update(struct rsnd_dai_stream *io,
				   struct rsnd_mod *mod)
{
	struct rsnd_dvc *dvc = rsnd_mod_to_dvc(mod);
	u32 zcmcr = 0;
	u32 vrpdr = 0;
	u32 vrdbr = 0;
	int i;

	for (i = 0; i < rsnd_kctrl_size(dvc->mute); i++)
		zcmcr |= (!!rsnd_kctrl_valm(dvc->mute, i)) << i;

	if (rsnd_kctrl_vals(dvc->ren)) {
		vrpdr = rsnd_dvc_get_vrpdr(dvc);
		vrdbr = rsnd_dvc_get_vrdbr(dvc);
	}

	/* Disable DVC Register access */
	rsnd_mod_write(mod, DVC_DVUER, 0);

	/* Zero Cross Mute Function */
	rsnd_mod_write(mod, DVC_ZCMCR, zcmcr);

	/* Volume Ramp Function */
	rsnd_mod_write(mod, DVC_VRPDR, vrpdr);
	rsnd_mod_write(mod, DVC_VRDBR, vrdbr);
	/* add DVC_VRWTR here */

	/* Digital Volume Function Parameter */
	rsnd_dvc_volume_parameter(io, mod);

	/* Enable DVC Register access */
	rsnd_mod_write(mod, DVC_DVUER, 1);
}