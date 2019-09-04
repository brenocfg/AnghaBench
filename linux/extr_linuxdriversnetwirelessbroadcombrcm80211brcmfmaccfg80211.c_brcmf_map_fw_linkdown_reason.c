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
typedef  int /*<<< orphan*/  u16 ;
struct brcmf_event_msg {int event_code; int /*<<< orphan*/  reason; } ;

/* Variables and functions */
#define  BRCMF_E_DEAUTH 131 
#define  BRCMF_E_DEAUTH_IND 130 
#define  BRCMF_E_DISASSOC_IND 129 
#define  BRCMF_E_LINK 128 

__attribute__((used)) static u16 brcmf_map_fw_linkdown_reason(const struct brcmf_event_msg *e)
{
	u16 reason;

	switch (e->event_code) {
	case BRCMF_E_DEAUTH:
	case BRCMF_E_DEAUTH_IND:
	case BRCMF_E_DISASSOC_IND:
		reason = e->reason;
		break;
	case BRCMF_E_LINK:
	default:
		reason = 0;
		break;
	}
	return reason;
}