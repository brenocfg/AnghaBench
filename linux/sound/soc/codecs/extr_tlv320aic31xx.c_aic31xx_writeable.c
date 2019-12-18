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
#define  AIC31XX_ADCFLAG 136 
#define  AIC31XX_DACFLAG1 135 
#define  AIC31XX_DACFLAG2 134 
#define  AIC31XX_INTRADCFLAG 133 
#define  AIC31XX_INTRADCFLAG2 132 
#define  AIC31XX_INTRDACFLAG 131 
#define  AIC31XX_INTRDACFLAG2 130 
#define  AIC31XX_OFFLAG 129 
#define  AIC31XX_OT_FLAG 128 

__attribute__((used)) static bool aic31xx_writeable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case AIC31XX_OT_FLAG:
	case AIC31XX_ADCFLAG:
	case AIC31XX_DACFLAG1:
	case AIC31XX_DACFLAG2:
	case AIC31XX_OFFLAG: /* Sticky interrupt flags */
	case AIC31XX_INTRDACFLAG: /* Sticky interrupt flags */
	case AIC31XX_INTRADCFLAG: /* Sticky interrupt flags */
	case AIC31XX_INTRDACFLAG2:
	case AIC31XX_INTRADCFLAG2:
		return false;
	}
	return true;
}