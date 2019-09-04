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
struct rsnd_dai {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SSI_MODE0 ; 
 int /*<<< orphan*/  SSI_MODE1 ; 
 int /*<<< orphan*/  SSI_MODE2 ; 
 int /*<<< orphan*/  SSI_SYS_STATUS0 ; 
 int /*<<< orphan*/  SSI_SYS_STATUS1 ; 
 int /*<<< orphan*/  SSI_SYS_STATUS2 ; 
 int /*<<< orphan*/  SSI_SYS_STATUS3 ; 
 int /*<<< orphan*/  SSI_SYS_STATUS4 ; 
 int /*<<< orphan*/  SSI_SYS_STATUS5 ; 
 int /*<<< orphan*/  SSI_SYS_STATUS6 ; 
 int /*<<< orphan*/  SSI_SYS_STATUS7 ; 
 struct rsnd_dai* rsnd_io_to_rdai (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_mod_bset (struct rsnd_mod*,int /*<<< orphan*/ ,int,int) ; 
 int rsnd_mod_id (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rsnd_rdai_is_clk_master (struct rsnd_dai*) ; 
 scalar_t__ rsnd_ssi_is_pin_sharing (struct rsnd_dai_stream*) ; 
 int rsnd_ssi_multi_slaves_runtime (struct rsnd_dai_stream*) ; 
 int rsnd_ssi_use_busif (struct rsnd_dai_stream*) ; 

__attribute__((used)) static int rsnd_ssiu_init(struct rsnd_mod *mod,
			  struct rsnd_dai_stream *io,
			  struct rsnd_priv *priv)
{
	struct rsnd_dai *rdai = rsnd_io_to_rdai(io);
	u32 multi_ssi_slaves = rsnd_ssi_multi_slaves_runtime(io);
	int use_busif = rsnd_ssi_use_busif(io);
	int id = rsnd_mod_id(mod);
	u32 mask1, val1;
	u32 mask2, val2;

	/* clear status */
	switch (id) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		rsnd_mod_write(mod, SSI_SYS_STATUS0, 0xf << (id * 4));
		rsnd_mod_write(mod, SSI_SYS_STATUS2, 0xf << (id * 4));
		rsnd_mod_write(mod, SSI_SYS_STATUS4, 0xf << (id * 4));
		rsnd_mod_write(mod, SSI_SYS_STATUS6, 0xf << (id * 4));
		break;
	case 9:
		rsnd_mod_write(mod, SSI_SYS_STATUS1, 0xf << 4);
		rsnd_mod_write(mod, SSI_SYS_STATUS3, 0xf << 4);
		rsnd_mod_write(mod, SSI_SYS_STATUS5, 0xf << 4);
		rsnd_mod_write(mod, SSI_SYS_STATUS7, 0xf << 4);
		break;
	}

	/*
	 * SSI_MODE0
	 */
	rsnd_mod_bset(mod, SSI_MODE0, (1 << id), !use_busif << id);

	/*
	 * SSI_MODE1
	 */
	mask1 = (1 << 4) | (1 << 20);	/* mask sync bit */
	mask2 = (1 << 4);		/* mask sync bit */
	val1  = val2  = 0;
	if (id == 8) {
		/*
		 * SSI8 pin is sharing with SSI7, nothing to do.
		 */
	} else if (rsnd_ssi_is_pin_sharing(io)) {
		int shift = -1;

		switch (id) {
		case 1:
			shift = 0;
			break;
		case 2:
			shift = 2;
			break;
		case 4:
			shift = 16;
			break;
		default:
			return -EINVAL;
		}

		mask1 |= 0x3 << shift;
		val1 = rsnd_rdai_is_clk_master(rdai) ?
			0x2 << shift : 0x1 << shift;

	} else if (multi_ssi_slaves) {

		mask2 |= 0x00000007;
		mask1 |= 0x0000000f;

		switch (multi_ssi_slaves) {
		case 0x0206: /* SSI0/1/2/9 */
			val2 = (1 << 4) | /* SSI0129 sync */
				(rsnd_rdai_is_clk_master(rdai) ? 0x2 : 0x1);
			/* fall through */
		case 0x0006: /* SSI0/1/2 */
			val1 = rsnd_rdai_is_clk_master(rdai) ?
				0xa : 0x5;

			if (!val2)  /* SSI012 sync */
				val1 |= (1 << 4);
		}
	}

	rsnd_mod_bset(mod, SSI_MODE1, mask1, val1);
	rsnd_mod_bset(mod, SSI_MODE2, mask2, val2);

	return 0;
}