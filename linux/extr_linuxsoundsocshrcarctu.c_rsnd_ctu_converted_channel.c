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
struct rsnd_ctu {int channels; } ;

/* Variables and functions */
 struct rsnd_ctu* rsnd_mod_to_ctu (struct rsnd_mod*) ; 

int rsnd_ctu_converted_channel(struct rsnd_mod *mod)
{
	struct rsnd_ctu *ctu = rsnd_mod_to_ctu(mod);

	return ctu->channels;
}