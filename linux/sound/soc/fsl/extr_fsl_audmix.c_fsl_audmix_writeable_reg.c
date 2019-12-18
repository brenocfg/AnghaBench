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
#define  FSL_AUDMIX_ATCR0 138 
#define  FSL_AUDMIX_ATCR1 137 
#define  FSL_AUDMIX_ATIVAL0 136 
#define  FSL_AUDMIX_ATIVAL1 135 
#define  FSL_AUDMIX_ATSTPDN0 134 
#define  FSL_AUDMIX_ATSTPDN1 133 
#define  FSL_AUDMIX_ATSTPTGT0 132 
#define  FSL_AUDMIX_ATSTPTGT1 131 
#define  FSL_AUDMIX_ATSTPUP0 130 
#define  FSL_AUDMIX_ATSTPUP1 129 
#define  FSL_AUDMIX_CTR 128 

__attribute__((used)) static bool fsl_audmix_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case FSL_AUDMIX_CTR:
	case FSL_AUDMIX_ATCR0:
	case FSL_AUDMIX_ATIVAL0:
	case FSL_AUDMIX_ATSTPUP0:
	case FSL_AUDMIX_ATSTPDN0:
	case FSL_AUDMIX_ATSTPTGT0:
	case FSL_AUDMIX_ATCR1:
	case FSL_AUDMIX_ATIVAL1:
	case FSL_AUDMIX_ATSTPUP1:
	case FSL_AUDMIX_ATSTPDN1:
	case FSL_AUDMIX_ATSTPTGT1:
		return true;
	default:
		return false;
	}
}