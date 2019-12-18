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
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIX_MDBER ; 
 int /*<<< orphan*/  rsnd_mix_volume_parameter (struct rsnd_dai_stream*,struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rsnd_mix_volume_update(struct rsnd_dai_stream *io,
				  struct rsnd_mod *mod)
{
	/* Disable MIX dB setting */
	rsnd_mod_write(mod, MIX_MDBER, 0);

	/* common volume parameter */
	rsnd_mix_volume_parameter(io, mod);

	/* Enable MIX dB setting */
	rsnd_mod_write(mod, MIX_MDBER, 1);
}