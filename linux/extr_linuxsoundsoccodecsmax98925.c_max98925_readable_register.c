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
#define  MAX98925_ALC_HOLD_RLS 131 
#define  MAX98925_IRQ_CLEAR0 130 
#define  MAX98925_IRQ_CLEAR1 129 
#define  MAX98925_IRQ_CLEAR2 128 

__attribute__((used)) static bool max98925_readable_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MAX98925_IRQ_CLEAR0:
	case MAX98925_IRQ_CLEAR1:
	case MAX98925_IRQ_CLEAR2:
	case MAX98925_ALC_HOLD_RLS:
		return false;
	default:
		return true;
	}
}