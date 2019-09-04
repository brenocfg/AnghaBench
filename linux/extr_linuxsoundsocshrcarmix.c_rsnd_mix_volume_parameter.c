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
struct rsnd_mix {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  C ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  MIX_MDBAR ; 
 int /*<<< orphan*/  MIX_MDBBR ; 
 int /*<<< orphan*/  MIX_MDBCR ; 
 int /*<<< orphan*/  MIX_MDBDR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_mix_get_vol (struct rsnd_mix*,int /*<<< orphan*/ ) ; 
 struct rsnd_mix* rsnd_mod_to_mix (struct rsnd_mod*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 

__attribute__((used)) static void rsnd_mix_volume_parameter(struct rsnd_dai_stream *io,
				      struct rsnd_mod *mod)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(mod);
	struct device *dev = rsnd_priv_to_dev(priv);
	struct rsnd_mix *mix = rsnd_mod_to_mix(mod);
	u32 volA = rsnd_mix_get_vol(mix, A);
	u32 volB = rsnd_mix_get_vol(mix, B);
	u32 volC = rsnd_mix_get_vol(mix, C);
	u32 volD = rsnd_mix_get_vol(mix, D);

	dev_dbg(dev, "MIX A/B/C/D = %02x/%02x/%02x/%02x\n",
		volA, volB, volC, volD);

	rsnd_mod_write(mod, MIX_MDBAR, volA);
	rsnd_mod_write(mod, MIX_MDBBR, volB);
	rsnd_mod_write(mod, MIX_MDBCR, volC);
	rsnd_mod_write(mod, MIX_MDBDR, volD);
}