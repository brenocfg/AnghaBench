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
struct rsnd_ssiu {int id; } ;
struct rsnd_mod {int dummy; } ;

/* Variables and functions */
 struct rsnd_ssiu* rsnd_mod_to_ssiu (struct rsnd_mod*) ; 

__attribute__((used)) static int rsnd_ssiu_id(struct rsnd_mod *mod)
{
	struct rsnd_ssiu *ssiu = rsnd_mod_to_ssiu(mod);

	/* see rsnd_ssiu_probe() */
	return ssiu->id;
}