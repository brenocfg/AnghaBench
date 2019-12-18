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
struct rsnd_ctu {int /*<<< orphan*/ * sv; int /*<<< orphan*/  pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTU_ADINR ; 
 int /*<<< orphan*/  CTU_CPMDR ; 
 int /*<<< orphan*/  CTU_CTUIR ; 
 int /*<<< orphan*/  CTU_SCMDR ; 
 int /*<<< orphan*/  CTU_SVxxR (int,int) ; 
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
	int i, j;

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

	for (i = 0; i < 4; i++) {

		if (i >= scmdr)
			break;

		for (j = 0; j < RSND_MAX_CHANNELS; j++)
			rsnd_mod_write(mod, CTU_SVxxR(i, j), rsnd_kctrl_valm(ctu->sv[i], j));
	}

	rsnd_mod_write(mod, CTU_CTUIR, 0);
}