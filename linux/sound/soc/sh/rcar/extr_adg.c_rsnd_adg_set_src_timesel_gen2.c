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
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_adg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_EN ; 
 int /*<<< orphan*/  SRCIN_TIMSEL (int) ; 
 int /*<<< orphan*/  SRCOUT_TIMSEL (int) ; 
 int /*<<< orphan*/  rsnd_adg_get_timesel_ratio (struct rsnd_priv*,struct rsnd_dai_stream*,unsigned int,unsigned int,int*,int*,int*) ; 
 int /*<<< orphan*/  rsnd_mod_bset (struct rsnd_mod*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rsnd_mod_confirm_src (struct rsnd_mod*) ; 
 struct rsnd_mod* rsnd_mod_get (struct rsnd_adg*) ; 
 int rsnd_mod_id (struct rsnd_mod*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 struct rsnd_adg* rsnd_priv_to_adg (struct rsnd_priv*) ; 

int rsnd_adg_set_src_timesel_gen2(struct rsnd_mod *src_mod,
				  struct rsnd_dai_stream *io,
				  unsigned int in_rate,
				  unsigned int out_rate)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(src_mod);
	struct rsnd_adg *adg = rsnd_priv_to_adg(priv);
	struct rsnd_mod *adg_mod = rsnd_mod_get(adg);
	u32 in, out;
	u32 mask, en;
	int id = rsnd_mod_id(src_mod);
	int shift = (id % 2) ? 16 : 0;

	rsnd_mod_confirm_src(src_mod);

	rsnd_adg_get_timesel_ratio(priv, io,
				   in_rate, out_rate,
				   &in, &out, &en);

	in   = in	<< shift;
	out  = out	<< shift;
	mask = 0x0f1f	<< shift;

	rsnd_mod_bset(adg_mod, SRCIN_TIMSEL(id / 2),  mask, in);
	rsnd_mod_bset(adg_mod, SRCOUT_TIMSEL(id / 2), mask, out);

	if (en)
		rsnd_mod_bset(adg_mod, DIV_EN, en, en);

	return 0;
}