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
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int /*<<< orphan*/  parent_ssi_status; } ;
typedef  enum rsnd_mod_type { ____Placeholder_rsnd_mod_type } rsnd_mod_type ;

/* Variables and functions */
 int RSND_MOD_SSIP ; 
 int /*<<< orphan*/ * rsnd_mod_get_status (struct rsnd_mod*,struct rsnd_dai_stream*,int) ; 

__attribute__((used)) static u32 *rsnd_ssi_get_status(struct rsnd_mod *mod,
				struct rsnd_dai_stream *io,
				enum rsnd_mod_type type)
{
	/*
	 * SSIP (= SSI parent) needs to be special, otherwise,
	 * 2nd SSI might doesn't start. see also rsnd_mod_call()
	 *
	 * We can't include parent SSI status on SSI, because we don't know
	 * how many SSI requests parent SSI. Thus, it is localed on "io" now.
	 * ex) trouble case
	 *	Playback: SSI0
	 *	Capture : SSI1 (needs SSI0)
	 *
	 * 1) start Capture  ->	SSI0/SSI1 are started.
	 * 2) start Playback ->	SSI0 doesn't work, because it is already
	 *			marked as "started" on 1)
	 *
	 * OTOH, using each mod's status is good for MUX case.
	 * It doesn't need to start in 2nd start
	 * ex)
	 *	IO-0: SRC0 -> CTU1 -+-> MUX -> DVC -> SSIU -> SSI0
	 *			    |
	 *	IO-1: SRC1 -> CTU2 -+
	 *
	 * 1) start IO-0 ->	start SSI0
	 * 2) start IO-1 ->	SSI0 doesn't need to start, because it is
	 *			already started on 1)
	 */
	if (type == RSND_MOD_SSIP)
		return &io->parent_ssi_status;

	return rsnd_mod_get_status(mod, io, type);
}