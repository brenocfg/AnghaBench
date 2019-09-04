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
struct cs42l42_private {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int CS42L42_AUTO_HSBIAS_HIZ_MASK ; 
 int CS42L42_AUTO_HSBIAS_HIZ_SHIFT ; 
 int CS42L42_DETECT_MODE_MASK ; 
 int CS42L42_DETECT_MODE_SHIFT ; 
 int /*<<< orphan*/  CS42L42_DET_INT2_MASK ; 
 int CS42L42_HSBIAS_CTL_MASK ; 
 int CS42L42_HSBIAS_CTL_SHIFT ; 
 int CS42L42_HSBIAS_REF_MASK ; 
 int CS42L42_HSBIAS_REF_SHIFT ; 
 int /*<<< orphan*/  CS42L42_HSBIAS_SC_AUTOCTL ; 
 int CS42L42_HSBIAS_SENSE_EN_MASK ; 
 int CS42L42_HSBIAS_SENSE_EN_SHIFT ; 
 int CS42L42_HSBIAS_SENSE_TRIP_MASK ; 
 int CS42L42_HSBIAS_SENSE_TRIP_SHIFT ; 
 int CS42L42_HSDET_AUTO_TIME_MASK ; 
 int CS42L42_HSDET_AUTO_TIME_SHIFT ; 
 int /*<<< orphan*/  CS42L42_HSDET_CTL2 ; 
 int CS42L42_HSDET_CTRL_MASK ; 
 int CS42L42_HSDET_CTRL_SHIFT ; 
 int CS42L42_HSDET_SET_MASK ; 
 int CS42L42_HSDET_SET_SHIFT ; 
 int /*<<< orphan*/  CS42L42_MISC_DET_CTL ; 
 int CS42L42_M_DETECT_FT_MASK ; 
 int CS42L42_M_DETECT_FT_SHIFT ; 
 int CS42L42_M_DETECT_TF_MASK ; 
 int CS42L42_M_DETECT_TF_SHIFT ; 
 int CS42L42_M_HSBIAS_HIZ_MASK ; 
 int CS42L42_M_HSBIAS_HIZ_SHIFT ; 
 int CS42L42_M_SHORT_DET_MASK ; 
 int CS42L42_M_SHORT_DET_SHIFT ; 
 int CS42L42_M_SHORT_RLS_MASK ; 
 int CS42L42_M_SHORT_RLS_SHIFT ; 
 int CS42L42_PDN_MIC_LVL_DET_MASK ; 
 int CS42L42_PDN_MIC_LVL_DET_SHIFT ; 
 int CS42L42_TIP_SENSE_EN_MASK ; 
 int CS42L42_TIP_SENSE_EN_SHIFT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cs42l42_cancel_hs_type_detect(struct cs42l42_private *cs42l42)
{
	/* Mask button detect interrupts */
	regmap_update_bits(cs42l42->regmap,
		CS42L42_DET_INT2_MASK,
		CS42L42_M_DETECT_TF_MASK |
		CS42L42_M_DETECT_FT_MASK |
		CS42L42_M_HSBIAS_HIZ_MASK |
		CS42L42_M_SHORT_RLS_MASK |
		CS42L42_M_SHORT_DET_MASK,
		(1 << CS42L42_M_DETECT_TF_SHIFT) |
		(1 << CS42L42_M_DETECT_FT_SHIFT) |
		(1 << CS42L42_M_HSBIAS_HIZ_SHIFT) |
		(1 << CS42L42_M_SHORT_RLS_SHIFT) |
		(1 << CS42L42_M_SHORT_DET_SHIFT));

	/* Ground HS bias */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_MISC_DET_CTL,
				CS42L42_DETECT_MODE_MASK |
				CS42L42_HSBIAS_CTL_MASK |
				CS42L42_PDN_MIC_LVL_DET_MASK,
				(0 << CS42L42_DETECT_MODE_SHIFT) |
				(1 << CS42L42_HSBIAS_CTL_SHIFT) |
				(1 << CS42L42_PDN_MIC_LVL_DET_SHIFT));

	/* Set auto HS bias settings to default */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSBIAS_SC_AUTOCTL,
				CS42L42_HSBIAS_SENSE_EN_MASK |
				CS42L42_AUTO_HSBIAS_HIZ_MASK |
				CS42L42_TIP_SENSE_EN_MASK |
				CS42L42_HSBIAS_SENSE_TRIP_MASK,
				(0 << CS42L42_HSBIAS_SENSE_EN_SHIFT) |
				(0 << CS42L42_AUTO_HSBIAS_HIZ_SHIFT) |
				(0 << CS42L42_TIP_SENSE_EN_SHIFT) |
				(3 << CS42L42_HSBIAS_SENSE_TRIP_SHIFT));

	/* Set hs detect to manual, disabled mode */
	regmap_update_bits(cs42l42->regmap,
				CS42L42_HSDET_CTL2,
				CS42L42_HSDET_CTRL_MASK |
				CS42L42_HSDET_SET_MASK |
				CS42L42_HSBIAS_REF_MASK |
				CS42L42_HSDET_AUTO_TIME_MASK,
				(0 << CS42L42_HSDET_CTRL_SHIFT) |
				(2 << CS42L42_HSDET_SET_SHIFT) |
				(0 << CS42L42_HSBIAS_REF_SHIFT) |
				(3 << CS42L42_HSDET_AUTO_TIME_SHIFT));
}