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

/* Variables and functions */
 int /*<<< orphan*/  RSND_SSI_CLK_PIN_SHARE ; 
 int /*<<< orphan*/  rsnd_flags_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_mod_to_ssi (struct rsnd_mod*) ; 

int __rsnd_ssi_is_pin_sharing(struct rsnd_mod *mod)
{
	if (!mod)
		return 0;

	return !!(rsnd_flags_has(rsnd_mod_to_ssi(mod), RSND_SSI_CLK_PIN_SHARE));
}