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
#define  FSL_AUDMIX_ATCR0 143 
#define  FSL_AUDMIX_ATCR1 142 
#define  FSL_AUDMIX_ATIVAL0 141 
#define  FSL_AUDMIX_ATIVAL1 140 
#define  FSL_AUDMIX_ATSTP0 139 
#define  FSL_AUDMIX_ATSTP1 138 
#define  FSL_AUDMIX_ATSTPDN0 137 
#define  FSL_AUDMIX_ATSTPDN1 136 
#define  FSL_AUDMIX_ATSTPTGT0 135 
#define  FSL_AUDMIX_ATSTPTGT1 134 
#define  FSL_AUDMIX_ATSTPUP0 133 
#define  FSL_AUDMIX_ATSTPUP1 132 
#define  FSL_AUDMIX_ATTNVAL0 131 
#define  FSL_AUDMIX_ATTNVAL1 130 
#define  FSL_AUDMIX_CTR 129 
#define  FSL_AUDMIX_STR 128 

__attribute__((used)) static bool fsl_audmix_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case FSL_AUDMIX_CTR:
	case FSL_AUDMIX_STR:
	case FSL_AUDMIX_ATCR0:
	case FSL_AUDMIX_ATIVAL0:
	case FSL_AUDMIX_ATSTPUP0:
	case FSL_AUDMIX_ATSTPDN0:
	case FSL_AUDMIX_ATSTPTGT0:
	case FSL_AUDMIX_ATTNVAL0:
	case FSL_AUDMIX_ATSTP0:
	case FSL_AUDMIX_ATCR1:
	case FSL_AUDMIX_ATIVAL1:
	case FSL_AUDMIX_ATSTPUP1:
	case FSL_AUDMIX_ATSTPDN1:
	case FSL_AUDMIX_ATSTPTGT1:
	case FSL_AUDMIX_ATTNVAL1:
	case FSL_AUDMIX_ATSTP1:
		return true;
	default:
		return false;
	}
}