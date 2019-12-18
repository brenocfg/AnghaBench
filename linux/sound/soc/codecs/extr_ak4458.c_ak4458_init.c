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
struct ak4458_priv {scalar_t__ mute_gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4458_00_CONTROL1 ; 
 int /*<<< orphan*/  ak4458_power_on (struct ak4458_priv*) ; 
 int ak4458_rstn_control (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 struct ak4458_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ak4458_init(struct snd_soc_component *component)
{
	struct ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);
	int ret;

	/* External Mute ON */
	if (ak4458->mute_gpiod)
		gpiod_set_value_cansleep(ak4458->mute_gpiod, 1);

	ak4458_power_on(ak4458);

	ret = snd_soc_component_update_bits(component, AK4458_00_CONTROL1,
			    0x80, 0x80);   /* ACKS bit = 1; 10000000 */
	if (ret < 0)
		return ret;

	return ak4458_rstn_control(component, 1);
}