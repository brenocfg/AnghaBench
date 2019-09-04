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
#define  STA529_ADCCFG 139 
#define  STA529_CKOCFG 138 
#define  STA529_FFXCFG0 137 
#define  STA529_FFXCFG1 136 
#define  STA529_LVOL 135 
#define  STA529_MISC 134 
#define  STA529_MVOL 133 
#define  STA529_P2SCFG0 132 
#define  STA529_P2SCFG1 131 
#define  STA529_RVOL 130 
#define  STA529_S2PCFG0 129 
#define  STA529_S2PCFG1 128 

__attribute__((used)) static bool sta529_readable(struct device *dev, unsigned int reg)
{
	switch (reg) {

	case STA529_FFXCFG0:
	case STA529_FFXCFG1:
	case STA529_MVOL:
	case STA529_LVOL:
	case STA529_RVOL:
	case STA529_S2PCFG0:
	case STA529_S2PCFG1:
	case STA529_P2SCFG0:
	case STA529_P2SCFG1:
	case STA529_ADCCFG:
	case STA529_CKOCFG:
	case STA529_MISC:
		return true;
	default:
		return false;
	}
}