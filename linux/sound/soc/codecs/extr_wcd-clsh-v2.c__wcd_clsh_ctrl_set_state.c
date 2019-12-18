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
struct wcd_clsh_ctrl {int dummy; } ;

/* Variables and functions */
#define  WCD_CLSH_STATE_EAR 131 
#define  WCD_CLSH_STATE_HPHL 130 
#define  WCD_CLSH_STATE_HPHR 129 
#define  WCD_CLSH_STATE_LO 128 
 int /*<<< orphan*/  wcd_clsh_state_ear (struct wcd_clsh_ctrl*,int,int,int) ; 
 int /*<<< orphan*/  wcd_clsh_state_hph_l (struct wcd_clsh_ctrl*,int,int,int) ; 
 int /*<<< orphan*/  wcd_clsh_state_hph_r (struct wcd_clsh_ctrl*,int,int,int) ; 
 int /*<<< orphan*/  wcd_clsh_state_lo (struct wcd_clsh_ctrl*,int,int,int) ; 

__attribute__((used)) static int _wcd_clsh_ctrl_set_state(struct wcd_clsh_ctrl *ctrl, int req_state,
				    bool is_enable, int mode)
{
	switch (req_state) {
	case WCD_CLSH_STATE_EAR:
		wcd_clsh_state_ear(ctrl, req_state, is_enable, mode);
		break;
	case WCD_CLSH_STATE_HPHL:
		wcd_clsh_state_hph_l(ctrl, req_state, is_enable, mode);
		break;
	case WCD_CLSH_STATE_HPHR:
		wcd_clsh_state_hph_r(ctrl, req_state, is_enable, mode);
		break;
		break;
	case WCD_CLSH_STATE_LO:
		wcd_clsh_state_lo(ctrl, req_state, is_enable, mode);
		break;
	default:
		break;
	}

	return 0;
}