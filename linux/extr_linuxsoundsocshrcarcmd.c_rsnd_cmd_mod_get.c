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
struct rsnd_priv {scalar_t__ cmd; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_cmd {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int rsnd_cmd_nr (struct rsnd_priv*) ; 
 struct rsnd_mod* rsnd_mod_get (struct rsnd_cmd*) ; 

__attribute__((used)) static struct rsnd_mod *rsnd_cmd_mod_get(struct rsnd_priv *priv, int id)
{
	if (WARN_ON(id < 0 || id >= rsnd_cmd_nr(priv)))
		id = 0;

	return rsnd_mod_get((struct rsnd_cmd *)(priv->cmd) + id);
}