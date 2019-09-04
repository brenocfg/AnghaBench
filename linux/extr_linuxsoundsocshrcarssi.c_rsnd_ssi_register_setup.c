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
struct rsnd_ssi {int wsr; int cr_own; int cr_clk; int cr_mode; int cr_en; } ;
struct rsnd_mod {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSICR ; 
 int /*<<< orphan*/  SSIWSR ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rsnd_ssi_register_setup(struct rsnd_mod *mod)
{
	struct rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);

	rsnd_mod_write(mod, SSIWSR,	ssi->wsr);
	rsnd_mod_write(mod, SSICR,	ssi->cr_own	|
					ssi->cr_clk	|
					ssi->cr_mode	|
					ssi->cr_en);
}