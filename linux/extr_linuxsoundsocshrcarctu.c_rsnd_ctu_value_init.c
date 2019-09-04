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
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_ctu {int /*<<< orphan*/  sv3; int /*<<< orphan*/  sv2; int /*<<< orphan*/  sv1; int /*<<< orphan*/  sv0; int /*<<< orphan*/  pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTU_ADINR ; 
 int /*<<< orphan*/  CTU_CPMDR ; 
 int /*<<< orphan*/  CTU_CTUIR ; 
 int /*<<< orphan*/  CTU_SCMDR ; 
 int /*<<< orphan*/  CTU_SV00R ; 
 int /*<<< orphan*/  CTU_SV01R ; 
 int /*<<< orphan*/  CTU_SV02R ; 
 int /*<<< orphan*/  CTU_SV03R ; 
 int /*<<< orphan*/  CTU_SV04R ; 
 int /*<<< orphan*/  CTU_SV05R ; 
 int /*<<< orphan*/  CTU_SV06R ; 
 int /*<<< orphan*/  CTU_SV07R ; 
 int /*<<< orphan*/  CTU_SV10R ; 
 int /*<<< orphan*/  CTU_SV11R ; 
 int /*<<< orphan*/  CTU_SV12R ; 
 int /*<<< orphan*/  CTU_SV13R ; 
 int /*<<< orphan*/  CTU_SV14R ; 
 int /*<<< orphan*/  CTU_SV15R ; 
 int /*<<< orphan*/  CTU_SV16R ; 
 int /*<<< orphan*/  CTU_SV17R ; 
 int /*<<< orphan*/  CTU_SV20R ; 
 int /*<<< orphan*/  CTU_SV21R ; 
 int /*<<< orphan*/  CTU_SV22R ; 
 int /*<<< orphan*/  CTU_SV23R ; 
 int /*<<< orphan*/  CTU_SV24R ; 
 int /*<<< orphan*/  CTU_SV25R ; 
 int /*<<< orphan*/  CTU_SV26R ; 
 int /*<<< orphan*/  CTU_SV27R ; 
 int /*<<< orphan*/  CTU_SV30R ; 
 int /*<<< orphan*/  CTU_SV31R ; 
 int /*<<< orphan*/  CTU_SV32R ; 
 int /*<<< orphan*/  CTU_SV33R ; 
 int /*<<< orphan*/  CTU_SV34R ; 
 int /*<<< orphan*/  CTU_SV35R ; 
 int /*<<< orphan*/  CTU_SV36R ; 
 int /*<<< orphan*/  CTU_SV37R ; 
 int RSND_MAX_CHANNELS ; 
 int rsnd_kctrl_valm (int /*<<< orphan*/ ,int) ; 
 struct rsnd_ctu* rsnd_mod_to_ctu (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 int rsnd_runtime_channel_original (struct rsnd_dai_stream*) ; 

__attribute__((used)) static void rsnd_ctu_value_init(struct rsnd_dai_stream *io,
			       struct rsnd_mod *mod)
{
	struct rsnd_ctu *ctu = rsnd_mod_to_ctu(mod);
	u32 cpmdr = 0;
	u32 scmdr = 0;
	int i;

	for (i = 0; i < RSND_MAX_CHANNELS; i++) {
		u32 val = rsnd_kctrl_valm(ctu->pass, i);

		cpmdr |= val << (28 - (i * 4));

		if ((val > 0x8) && (scmdr < (val - 0x8)))
			scmdr = val - 0x8;
	}

	rsnd_mod_write(mod, CTU_CTUIR, 1);

	rsnd_mod_write(mod, CTU_ADINR, rsnd_runtime_channel_original(io));

	rsnd_mod_write(mod, CTU_CPMDR, cpmdr);

	rsnd_mod_write(mod, CTU_SCMDR, scmdr);

	if (scmdr > 0) {
		rsnd_mod_write(mod, CTU_SV00R, rsnd_kctrl_valm(ctu->sv0, 0));
		rsnd_mod_write(mod, CTU_SV01R, rsnd_kctrl_valm(ctu->sv0, 1));
		rsnd_mod_write(mod, CTU_SV02R, rsnd_kctrl_valm(ctu->sv0, 2));
		rsnd_mod_write(mod, CTU_SV03R, rsnd_kctrl_valm(ctu->sv0, 3));
		rsnd_mod_write(mod, CTU_SV04R, rsnd_kctrl_valm(ctu->sv0, 4));
		rsnd_mod_write(mod, CTU_SV05R, rsnd_kctrl_valm(ctu->sv0, 5));
		rsnd_mod_write(mod, CTU_SV06R, rsnd_kctrl_valm(ctu->sv0, 6));
		rsnd_mod_write(mod, CTU_SV07R, rsnd_kctrl_valm(ctu->sv0, 7));
	}
	if (scmdr > 1) {
		rsnd_mod_write(mod, CTU_SV10R, rsnd_kctrl_valm(ctu->sv1, 0));
		rsnd_mod_write(mod, CTU_SV11R, rsnd_kctrl_valm(ctu->sv1, 1));
		rsnd_mod_write(mod, CTU_SV12R, rsnd_kctrl_valm(ctu->sv1, 2));
		rsnd_mod_write(mod, CTU_SV13R, rsnd_kctrl_valm(ctu->sv1, 3));
		rsnd_mod_write(mod, CTU_SV14R, rsnd_kctrl_valm(ctu->sv1, 4));
		rsnd_mod_write(mod, CTU_SV15R, rsnd_kctrl_valm(ctu->sv1, 5));
		rsnd_mod_write(mod, CTU_SV16R, rsnd_kctrl_valm(ctu->sv1, 6));
		rsnd_mod_write(mod, CTU_SV17R, rsnd_kctrl_valm(ctu->sv1, 7));
	}
	if (scmdr > 2) {
		rsnd_mod_write(mod, CTU_SV20R, rsnd_kctrl_valm(ctu->sv2, 0));
		rsnd_mod_write(mod, CTU_SV21R, rsnd_kctrl_valm(ctu->sv2, 1));
		rsnd_mod_write(mod, CTU_SV22R, rsnd_kctrl_valm(ctu->sv2, 2));
		rsnd_mod_write(mod, CTU_SV23R, rsnd_kctrl_valm(ctu->sv2, 3));
		rsnd_mod_write(mod, CTU_SV24R, rsnd_kctrl_valm(ctu->sv2, 4));
		rsnd_mod_write(mod, CTU_SV25R, rsnd_kctrl_valm(ctu->sv2, 5));
		rsnd_mod_write(mod, CTU_SV26R, rsnd_kctrl_valm(ctu->sv2, 6));
		rsnd_mod_write(mod, CTU_SV27R, rsnd_kctrl_valm(ctu->sv2, 7));
	}
	if (scmdr > 3) {
		rsnd_mod_write(mod, CTU_SV30R, rsnd_kctrl_valm(ctu->sv3, 0));
		rsnd_mod_write(mod, CTU_SV31R, rsnd_kctrl_valm(ctu->sv3, 1));
		rsnd_mod_write(mod, CTU_SV32R, rsnd_kctrl_valm(ctu->sv3, 2));
		rsnd_mod_write(mod, CTU_SV33R, rsnd_kctrl_valm(ctu->sv3, 3));
		rsnd_mod_write(mod, CTU_SV34R, rsnd_kctrl_valm(ctu->sv3, 4));
		rsnd_mod_write(mod, CTU_SV35R, rsnd_kctrl_valm(ctu->sv3, 5));
		rsnd_mod_write(mod, CTU_SV36R, rsnd_kctrl_valm(ctu->sv3, 6));
		rsnd_mod_write(mod, CTU_SV37R, rsnd_kctrl_valm(ctu->sv3, 7));
	}

	rsnd_mod_write(mod, CTU_CTUIR, 0);
}