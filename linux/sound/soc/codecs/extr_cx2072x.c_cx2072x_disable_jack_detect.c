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
struct snd_soc_component {int dummy; } ;
struct cx2072x_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2072X_PORTA_UNSOLICITED_RESPONSE ; 
 int /*<<< orphan*/  CX2072X_UM_INTERRUPT_CRTL_E ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx2072x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void cx2072x_disable_jack_detect(struct snd_soc_component *codec)
{
	struct cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);

	regmap_write(cx2072x->regmap, CX2072X_UM_INTERRUPT_CRTL_E, 0);
	regmap_write(cx2072x->regmap, CX2072X_PORTA_UNSOLICITED_RESPONSE, 0);
}