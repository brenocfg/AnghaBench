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
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int /*<<< orphan*/ ** mod; } ;
typedef  enum rsnd_mod_type { ____Placeholder_rsnd_mod_type } rsnd_mod_type ;

/* Variables and functions */

__attribute__((used)) static void rsnd_dai_disconnect(struct rsnd_mod *mod,
				struct rsnd_dai_stream *io,
				enum rsnd_mod_type type)
{
	io->mod[type] = NULL;
}