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
struct rsnd_adg {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_CLK_SEL (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  rsnd_mod_bset (struct rsnd_mod*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rsnd_mod_confirm_ssi (struct rsnd_mod*) ; 
 struct rsnd_mod* rsnd_mod_get (struct rsnd_adg*) ; 
 int rsnd_mod_id (struct rsnd_mod*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 struct rsnd_adg* rsnd_priv_to_adg (struct rsnd_priv*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 

__attribute__((used)) static void rsnd_adg_set_ssi_clk(struct rsnd_mod *ssi_mod, u32 val)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(ssi_mod);
	struct rsnd_adg *adg = rsnd_priv_to_adg(priv);
	struct rsnd_mod *adg_mod = rsnd_mod_get(adg);
	struct device *dev = rsnd_priv_to_dev(priv);
	int id = rsnd_mod_id(ssi_mod);
	int shift = (id % 4) * 8;
	u32 mask = 0xFF << shift;

	rsnd_mod_confirm_ssi(ssi_mod);

	val = val << shift;

	/*
	 * SSI 8 is not connected to ADG.
	 * it works with SSI 7
	 */
	if (id == 8)
		return;

	rsnd_mod_bset(adg_mod, AUDIO_CLK_SEL(id / 4), mask, val);

	dev_dbg(dev, "AUDIO_CLK_SEL is 0x%x\n", val);
}