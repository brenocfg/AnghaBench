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
 int /*<<< orphan*/  CMDOUT_TIMSEL ; 
 int /*<<< orphan*/  rsnd_adg_get_timesel_ratio (struct rsnd_priv*,struct rsnd_dai_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsnd_mod_bset (struct rsnd_mod*,int /*<<< orphan*/ ,int,int) ; 
 struct rsnd_mod* rsnd_mod_get (struct rsnd_adg*) ; 
 int rsnd_mod_id (struct rsnd_mod*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 struct rsnd_adg* rsnd_priv_to_adg (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_src_get_in_rate (struct rsnd_priv*,struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_src_get_out_rate (struct rsnd_priv*,struct rsnd_dai_stream*) ; 

int rsnd_adg_set_cmd_timsel_gen2(struct rsnd_mod *cmd_mod,
				 struct rsnd_dai_stream *io)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(cmd_mod);
	struct rsnd_adg *adg = rsnd_priv_to_adg(priv);
	struct rsnd_mod *adg_mod = rsnd_mod_get(adg);
	int id = rsnd_mod_id(cmd_mod);
	int shift = (id % 2) ? 16 : 0;
	u32 mask, val;

	rsnd_adg_get_timesel_ratio(priv, io,
				   rsnd_src_get_in_rate(priv, io),
				   rsnd_src_get_out_rate(priv, io),
				   NULL, &val, NULL);

	val  = val	<< shift;
	mask = 0x0f1f	<< shift;

	rsnd_mod_bset(adg_mod, CMDOUT_TIMSEL, mask, val);

	return 0;
}