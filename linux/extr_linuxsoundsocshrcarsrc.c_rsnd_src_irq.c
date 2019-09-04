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
struct rsnd_src {int irq; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int OUF_SRC (int) ; 
 int /*<<< orphan*/  SCU_SYS_INT_EN0 ; 
 int /*<<< orphan*/  SCU_SYS_INT_EN1 ; 
 int /*<<< orphan*/  SRC_INT_ENABLE0 ; 
 int /*<<< orphan*/  rsnd_mod_bset (struct rsnd_mod*,int /*<<< orphan*/ ,int,int) ; 
 int rsnd_mod_id (struct rsnd_mod*) ; 
 struct rsnd_src* rsnd_mod_to_src (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rsnd_src_sync_is_enabled (struct rsnd_mod*) ; 

__attribute__((used)) static int rsnd_src_irq(struct rsnd_mod *mod,
			struct rsnd_dai_stream *io,
			struct rsnd_priv *priv,
			int enable)
{
	struct rsnd_src *src = rsnd_mod_to_src(mod);
	u32 sys_int_val, int_val, sys_int_mask;
	int irq = src->irq;
	int id = rsnd_mod_id(mod);

	sys_int_val =
	sys_int_mask = OUF_SRC(id);
	int_val = 0x3300;

	/*
	 * IRQ is not supported on non-DT
	 * see
	 *	rsnd_src_probe_()
	 */
	if ((irq <= 0) || !enable) {
		sys_int_val = 0;
		int_val = 0;
	}

	/*
	 * WORKAROUND
	 *
	 * ignore over flow error when rsnd_src_sync_is_enabled()
	 */
	if (rsnd_src_sync_is_enabled(mod))
		sys_int_val = sys_int_val & 0xffff;

	rsnd_mod_write(mod, SRC_INT_ENABLE0, int_val);
	rsnd_mod_bset(mod, SCU_SYS_INT_EN0, sys_int_mask, sys_int_val);
	rsnd_mod_bset(mod, SCU_SYS_INT_EN1, sys_int_mask, sys_int_val);

	return 0;
}