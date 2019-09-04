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
 int /*<<< orphan*/  CTU_SWRSR ; 
 int /*<<< orphan*/  rsnd_mod_write (struct rsnd_mod*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rsnd_ctu_activation(struct rsnd_mod *mod)
{
	rsnd_mod_write(mod, CTU_SWRSR, 0);
	rsnd_mod_write(mod, CTU_SWRSR, 1);
}