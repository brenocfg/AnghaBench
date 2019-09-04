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
struct brcmf_p2p_pub_act_frame {scalar_t__ category; scalar_t__ action; scalar_t__ oui_type; int /*<<< orphan*/  oui; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_OUI ; 
 int /*<<< orphan*/  P2P_OUI_LEN ; 
 scalar_t__ P2P_PUB_AF_ACTION ; 
 scalar_t__ P2P_PUB_AF_CATEGORY ; 
 scalar_t__ P2P_VER ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool brcmf_p2p_is_pub_action(void *frame, u32 frame_len)
{
	struct brcmf_p2p_pub_act_frame *pact_frm;

	if (frame == NULL)
		return false;

	pact_frm = (struct brcmf_p2p_pub_act_frame *)frame;
	if (frame_len < sizeof(struct brcmf_p2p_pub_act_frame) - 1)
		return false;

	if (pact_frm->category == P2P_PUB_AF_CATEGORY &&
	    pact_frm->action == P2P_PUB_AF_ACTION &&
	    pact_frm->oui_type == P2P_VER &&
	    memcmp(pact_frm->oui, P2P_OUI, P2P_OUI_LEN) == 0)
		return true;

	return false;
}