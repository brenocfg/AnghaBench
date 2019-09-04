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
struct rsnd_mod {int dummy; } ;
struct rsnd_mix {int /*<<< orphan*/  rdw; int /*<<< orphan*/  rup; int /*<<< orphan*/  ren; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIX_ADINR ; 
 int /*<<< orphan*/  MIX_MIXIR ; 
 int /*<<< orphan*/  MIX_MIXMR ; 
 int /*<<< orphan*/  MIX_MVPDR ; 
 int rsnd_kctrl_vals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_mix_volume_parameter (struct rsnd_dai_stream*,struct rsnd_mod*) ; 
 struct rsnd_mix* rsnd_mod_to_mix (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 int rsnd_runtime_channel_after_ctu (struct rsnd_dai_stream*) ; 

__attribute__((used)) static void rsnd_mix_volume_init(struct rsnd_dai_stream *io,
				 struct rsnd_mod *mod)
{
	struct rsnd_mix *mix = rsnd_mod_to_mix(mod);

	rsnd_mod_write(mod, MIX_MIXIR, 1);

	/* General Information */
	rsnd_mod_write(mod, MIX_ADINR, rsnd_runtime_channel_after_ctu(io));

	/* volume step */
	rsnd_mod_write(mod, MIX_MIXMR, rsnd_kctrl_vals(mix->ren));
	rsnd_mod_write(mod, MIX_MVPDR, rsnd_kctrl_vals(mix->rup) << 8 |
				       rsnd_kctrl_vals(mix->rdw));

	/* common volume parameter */
	rsnd_mix_volume_parameter(io, mod);

	rsnd_mod_write(mod, MIX_MIXIR, 0);
}