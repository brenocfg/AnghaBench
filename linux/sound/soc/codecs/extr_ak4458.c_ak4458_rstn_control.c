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

/* Variables and functions */
 int /*<<< orphan*/  AK4458_00_CONTROL1 ; 
 int /*<<< orphan*/  AK4458_RSTN_MASK ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ak4458_rstn_control(struct snd_soc_component *component, int bit)
{
	int ret;

	if (bit)
		ret = snd_soc_component_update_bits(component,
					  AK4458_00_CONTROL1,
					  AK4458_RSTN_MASK,
					  0x1);
	else
		ret = snd_soc_component_update_bits(component,
					  AK4458_00_CONTROL1,
					  AK4458_RSTN_MASK,
					  0x0);
	if (ret < 0)
		return ret;

	return 0;
}