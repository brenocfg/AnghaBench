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
typedef  int uint ;
typedef  int u64 ;
typedef  int u32 ;
struct snd_pcm_runtime {int dummy; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRC_ADINR ; 
 int /*<<< orphan*/  SRC_BSDSR ; 
 int /*<<< orphan*/  SRC_BSISR ; 
 int /*<<< orphan*/  SRC_BUSIF_DALIGN ; 
 int /*<<< orphan*/  SRC_IFSCR ; 
 int /*<<< orphan*/  SRC_IFSVR ; 
 int /*<<< orphan*/  SRC_I_BUSIF_MODE ; 
 int /*<<< orphan*/  SRC_O_BUSIF_MODE ; 
 int /*<<< orphan*/  SRC_ROUTE_MODE0 ; 
 int /*<<< orphan*/  SRC_SRCCR ; 
 int /*<<< orphan*/  SRC_SRCIR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  rsnd_adg_set_src_timesel_gen2 (struct rsnd_mod*,struct rsnd_dai_stream*,int,int) ; 
 int rsnd_get_adinr_bit (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 int rsnd_get_busif_shift (struct rsnd_dai_stream*,struct rsnd_mod*) ; 
 int rsnd_get_dalign (struct rsnd_mod*,struct rsnd_dai_stream*) ; 
 int rsnd_io_is_play (struct rsnd_dai_stream*) ; 
 struct snd_pcm_runtime* rsnd_io_to_runtime (struct rsnd_dai_stream*) ; 
 int rsnd_mod_id (struct rsnd_mod*) ; 
 struct rsnd_priv* rsnd_mod_to_priv (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 int rsnd_runtime_channel_original (struct rsnd_dai_stream*) ; 
 int rsnd_src_get_in_rate (struct rsnd_priv*,struct rsnd_dai_stream*) ; 
 int rsnd_src_get_out_rate (struct rsnd_priv*,struct rsnd_dai_stream*) ; 
 int rsnd_src_sync_is_enabled (struct rsnd_mod*) ; 

__attribute__((used)) static void rsnd_src_set_convert_rate(struct rsnd_dai_stream *io,
				      struct rsnd_mod *mod)
{
	struct rsnd_priv *priv = rsnd_mod_to_priv(mod);
	struct device *dev = rsnd_priv_to_dev(priv);
	struct snd_pcm_runtime *runtime = rsnd_io_to_runtime(io);
	int is_play = rsnd_io_is_play(io);
	int use_src = 0;
	u32 fin, fout;
	u32 ifscr, fsrate, adinr;
	u32 cr, route;
	u32 bsdsr, bsisr;
	u32 i_busif, o_busif, tmp;
	uint ratio;

	if (!runtime)
		return;

	fin  = rsnd_src_get_in_rate(priv, io);
	fout = rsnd_src_get_out_rate(priv, io);

	/* 6 - 1/6 are very enough ratio for SRC_BSDSR */
	if (fin == fout)
		ratio = 0;
	else if (fin > fout)
		ratio = 100 * fin / fout;
	else
		ratio = 100 * fout / fin;

	if (ratio > 600) {
		dev_err(dev, "FSO/FSI ratio error\n");
		return;
	}

	use_src = (fin != fout) | rsnd_src_sync_is_enabled(mod);

	/*
	 * SRC_ADINR
	 */
	adinr = rsnd_get_adinr_bit(mod, io) |
		rsnd_runtime_channel_original(io);

	/*
	 * SRC_IFSCR / SRC_IFSVR
	 */
	ifscr = 0;
	fsrate = 0;
	if (use_src) {
		u64 n;

		ifscr = 1;
		n = (u64)0x0400000 * fin;
		do_div(n, fout);
		fsrate = n;
	}

	/*
	 * SRC_SRCCR / SRC_ROUTE_MODE0
	 */
	cr	= 0x00011110;
	route	= 0x0;
	if (use_src) {
		route	= 0x1;

		if (rsnd_src_sync_is_enabled(mod)) {
			cr |= 0x1;
			route |= rsnd_io_is_play(io) ?
				(0x1 << 24) : (0x1 << 25);
		}
	}

	/*
	 * SRC_BSDSR / SRC_BSISR
	 */
	switch (rsnd_mod_id(mod)) {
	case 5:
	case 6:
	case 7:
	case 8:
		bsdsr = 0x02400000; /* 6 - 1/6 */
		bsisr = 0x00100060; /* 6 - 1/6 */
		break;
	default:
		bsdsr = 0x01800000; /* 6 - 1/6 */
		bsisr = 0x00100060 ;/* 6 - 1/6 */
		break;
	}

	/* BUSIF_MODE */
	tmp = rsnd_get_busif_shift(io, mod);
	i_busif = ( is_play ? tmp : 0) | 1;
	o_busif = (!is_play ? tmp : 0) | 1;

	rsnd_mod_write(mod, SRC_ROUTE_MODE0, route);

	rsnd_mod_write(mod, SRC_SRCIR, 1);	/* initialize */
	rsnd_mod_write(mod, SRC_ADINR, adinr);
	rsnd_mod_write(mod, SRC_IFSCR, ifscr);
	rsnd_mod_write(mod, SRC_IFSVR, fsrate);
	rsnd_mod_write(mod, SRC_SRCCR, cr);
	rsnd_mod_write(mod, SRC_BSDSR, bsdsr);
	rsnd_mod_write(mod, SRC_BSISR, bsisr);
	rsnd_mod_write(mod, SRC_SRCIR, 0);	/* cancel initialize */

	rsnd_mod_write(mod, SRC_I_BUSIF_MODE, i_busif);
	rsnd_mod_write(mod, SRC_O_BUSIF_MODE, o_busif);

	rsnd_mod_write(mod, SRC_BUSIF_DALIGN, rsnd_get_dalign(mod, io));

	rsnd_adg_set_src_timesel_gen2(mod, io, fin, fout);
}