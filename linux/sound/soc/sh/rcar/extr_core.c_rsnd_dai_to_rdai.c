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
struct snd_soc_dai {int /*<<< orphan*/  id; } ;
struct rsnd_priv {int dummy; } ;
struct rsnd_dai {int dummy; } ;

/* Variables and functions */
 struct rsnd_priv* rsnd_dai_to_priv (struct snd_soc_dai*) ; 
 struct rsnd_dai* rsnd_rdai_get (struct rsnd_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rsnd_dai *rsnd_dai_to_rdai(struct snd_soc_dai *dai)
{
	struct rsnd_priv *priv = rsnd_dai_to_priv(dai);

	return rsnd_rdai_get(priv, dai->id);
}