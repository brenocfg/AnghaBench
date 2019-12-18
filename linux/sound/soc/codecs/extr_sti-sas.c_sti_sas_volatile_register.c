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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int STIH407_AUDIO_GLUE_CTRL ; 

__attribute__((used)) static bool sti_sas_volatile_register(struct device *dev, unsigned int reg)
{
	if (reg == STIH407_AUDIO_GLUE_CTRL)
		return true;

	return false;
}