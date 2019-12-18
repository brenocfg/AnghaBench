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
struct wcd_clsh_ctrl {struct snd_soc_component* comp; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
#define  CLS_AB 131 
#define  CLS_H_HIFI 130 
#define  CLS_H_LP 129 
#define  CLS_H_NORMAL 128 
 int WCD9XXX_HPH_CONST_SEL_BYPASS ; 
 int WCD9XXX_HPH_CONST_SEL_HQ_PATH ; 
 int WCD9XXX_HPH_CONST_SEL_LP_PATH ; 
 int /*<<< orphan*/  WCD9XXX_HPH_CONST_SEL_L_MASK ; 
 int /*<<< orphan*/  WCD9XXX_HPH_L_EN ; 
 int /*<<< orphan*/  WCD9XXX_HPH_R_EN ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wcd_clsh_set_gain_path(struct wcd_clsh_ctrl *ctrl, int mode)
{
	struct snd_soc_component *comp = ctrl->comp;
	int val = 0;

	switch (mode) {
	case CLS_H_NORMAL:
	case CLS_AB:
		val = WCD9XXX_HPH_CONST_SEL_BYPASS;
		break;
	case CLS_H_HIFI:
		val = WCD9XXX_HPH_CONST_SEL_HQ_PATH;
		break;
	case CLS_H_LP:
		val = WCD9XXX_HPH_CONST_SEL_LP_PATH;
		break;
	}

	snd_soc_component_update_bits(comp, WCD9XXX_HPH_L_EN,
					WCD9XXX_HPH_CONST_SEL_L_MASK,
					val);

	snd_soc_component_update_bits(comp, WCD9XXX_HPH_R_EN,
					WCD9XXX_HPH_CONST_SEL_L_MASK,
					val);
}