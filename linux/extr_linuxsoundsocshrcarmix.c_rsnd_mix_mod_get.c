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
struct rsnd_priv {int dummy; } ;
struct rsnd_mod {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  rsnd_mix_get (struct rsnd_priv*,int) ; 
 int rsnd_mix_nr (struct rsnd_priv*) ; 
 struct rsnd_mod* rsnd_mod_get (int /*<<< orphan*/ ) ; 

struct rsnd_mod *rsnd_mix_mod_get(struct rsnd_priv *priv, int id)
{
	if (WARN_ON(id < 0 || id >= rsnd_mix_nr(priv)))
		id = 0;

	return rsnd_mod_get(rsnd_mix_get(priv, id));
}