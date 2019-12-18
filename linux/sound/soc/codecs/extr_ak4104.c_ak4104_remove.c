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
struct ak4104_private {int /*<<< orphan*/  regulator; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int AK4104_CONTROL1_PW ; 
 int AK4104_CONTROL1_RSTN ; 
 int /*<<< orphan*/  AK4104_REG_CONTROL1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct ak4104_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void ak4104_remove(struct snd_soc_component *component)
{
	struct ak4104_private *ak4104 = snd_soc_component_get_drvdata(component);

	regmap_update_bits(ak4104->regmap, AK4104_REG_CONTROL1,
			   AK4104_CONTROL1_PW | AK4104_CONTROL1_RSTN, 0);
	regulator_disable(ak4104->regulator);
}