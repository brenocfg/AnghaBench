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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 scalar_t__ DAC33_DEVICE_ID_MSB ; 
 int dac33_read (struct snd_soc_component*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int dac33_read_id(struct snd_soc_component *component)
{
	int i, ret = 0;
	u8 reg;

	for (i = 0; i < 3; i++) {
		ret = dac33_read(component, DAC33_DEVICE_ID_MSB + i, &reg);
		if (ret < 0)
			break;
	}

	return ret;
}