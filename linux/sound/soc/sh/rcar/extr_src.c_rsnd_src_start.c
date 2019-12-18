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

/* Variables and functions */
 int /*<<< orphan*/  SRC_CTRL ; 
 scalar_t__ rsnd_io_to_mod_dvc (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsnd_src_sync_is_enabled (struct rsnd_mod*) ; 

__attribute__((used)) static int rsnd_src_start(struct rsnd_mod *mod,
			  struct rsnd_dai_stream *io,
			  struct rsnd_priv *priv)
{
	u32 val;

	/*
	 * WORKAROUND
	 *
	 * Enable SRC output if you want to use sync convert together with DVC
	 */
	val = (rsnd_io_to_mod_dvc(io) && !rsnd_src_sync_is_enabled(mod)) ?
		0x01 : 0x11;

	rsnd_mod_write(mod, SRC_CTRL, val);

	return 0;
}