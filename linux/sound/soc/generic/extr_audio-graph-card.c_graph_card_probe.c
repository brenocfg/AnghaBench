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
struct snd_soc_card {int dummy; } ;
struct asoc_simple_priv {int /*<<< orphan*/  mic_jack; int /*<<< orphan*/  hp_jack; } ;

/* Variables and functions */
 int asoc_simple_init_hp (struct snd_soc_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int asoc_simple_init_mic (struct snd_soc_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct asoc_simple_priv* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int graph_card_probe(struct snd_soc_card *card)
{
	struct asoc_simple_priv *priv = snd_soc_card_get_drvdata(card);
	int ret;

	ret = asoc_simple_init_hp(card, &priv->hp_jack, NULL);
	if (ret < 0)
		return ret;

	ret = asoc_simple_init_mic(card, &priv->mic_jack, NULL);
	if (ret < 0)
		return ret;

	return 0;
}