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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct cx2072x_priv {int en_aec_ref; } ;

/* Variables and functions */
 struct cx2072x_priv* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx2072x_dsp_dai_probe(struct snd_soc_dai *dai)
{
	struct cx2072x_priv *cx2072x =
		snd_soc_component_get_drvdata(dai->component);

	cx2072x->en_aec_ref = true;
	return 0;
}