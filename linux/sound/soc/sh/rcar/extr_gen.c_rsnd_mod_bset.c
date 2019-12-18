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
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_gen {int /*<<< orphan*/ * regs; } ;
struct device {int dummy; } ;
typedef  enum rsnd_reg { ____Placeholder_rsnd_reg } rsnd_reg ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_fields_force_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_is_accessible_reg (struct rsnd_priv*,struct rsnd_gen*,int) ; 
 int /*<<< orphan*/  rsnd_mod_id_cmd (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_name (struct rsnd_mod*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 struct rsnd_gen* rsnd_priv_to_gen (struct rsnd_priv*) ; 
 int /*<<< orphan*/  rsnd_reg_name (struct rsnd_gen*,int) ; 

void rsnd_mod_bset(struct rsnd_mod *mod,
		   enum rsnd_reg reg, u32 mask, u32 data)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(mod);
	struct device *dev = rsnd_priv_to_dev(priv);
	struct rsnd_gen *gen = rsnd_priv_to_gen(priv);

	if (!rsnd_is_accessible_reg(priv, gen, reg))
		return;

	regmap_fields_force_update_bits(gen->regs[reg],
					rsnd_mod_id_cmd(mod), mask, data);

	dev_dbg(dev, "b %s - %-18s (%4d) : %08x/%08x\n",
		rsnd_mod_name(mod),
		rsnd_reg_name(gen, reg), reg, data, mask);

}