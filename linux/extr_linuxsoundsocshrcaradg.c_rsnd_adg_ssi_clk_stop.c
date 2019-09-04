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
 int /*<<< orphan*/  rsnd_adg_set_ssi_clk (struct rsnd_mod*,int /*<<< orphan*/ ) ; 

int rsnd_adg_ssi_clk_stop(struct rsnd_mod *ssi_mod)
{
	rsnd_adg_set_ssi_clk(ssi_mod, 0);

	return 0;
}