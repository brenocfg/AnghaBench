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
typedef  int u32 ;
struct brcmf_p2psd_gas_pub_act_frame {scalar_t__ category; scalar_t__ action; } ;

/* Variables and functions */
 scalar_t__ P2PSD_ACTION_CATEGORY ; 
 scalar_t__ P2PSD_ACTION_ID_GAS_CREQ ; 
 scalar_t__ P2PSD_ACTION_ID_GAS_CRESP ; 
 scalar_t__ P2PSD_ACTION_ID_GAS_IREQ ; 
 scalar_t__ P2PSD_ACTION_ID_GAS_IRESP ; 

__attribute__((used)) static bool brcmf_p2p_is_gas_action(void *frame, u32 frame_len)
{
	struct brcmf_p2psd_gas_pub_act_frame *sd_act_frm;

	if (frame == NULL)
		return false;

	sd_act_frm = (struct brcmf_p2psd_gas_pub_act_frame *)frame;
	if (frame_len < sizeof(struct brcmf_p2psd_gas_pub_act_frame) - 1)
		return false;

	if (sd_act_frm->category != P2PSD_ACTION_CATEGORY)
		return false;

	if (sd_act_frm->action == P2PSD_ACTION_ID_GAS_IREQ ||
	    sd_act_frm->action == P2PSD_ACTION_ID_GAS_IRESP ||
	    sd_act_frm->action == P2PSD_ACTION_ID_GAS_CREQ ||
	    sd_act_frm->action == P2PSD_ACTION_ID_GAS_CRESP)
		return true;

	return false;
}