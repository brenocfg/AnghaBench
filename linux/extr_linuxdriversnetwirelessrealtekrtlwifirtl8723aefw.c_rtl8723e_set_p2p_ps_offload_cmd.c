#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl_p2p_ps_info {int noa_num; int* noa_duration; int* noa_interval; int* noa_start_time; int* noa_count_type; int opp_ps; int p2p_ps_state; int /*<<< orphan*/  ctwindow; } ;
struct rtl_ps_ctl {struct rtl_p2p_ps_info p2p_ps_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;
struct rtl_priv {TYPE_1__ mac80211; } ;
struct p2p_ps_offload_t {int ctwindow_en; int noa0_en; int noa1_en; int offload_en; int role; int discovery; int /*<<< orphan*/  allstasleep; } ;
struct rtl_hal {struct p2p_ps_offload_t p2p_ps_offload; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  H2C_P2P_PS_OFFLOAD ; 
#define  P2P_PS_DISABLE 131 
#define  P2P_PS_ENABLE 130 
#define  P2P_PS_SCAN 129 
#define  P2P_PS_SCAN_DONE 128 
 int /*<<< orphan*/  P2P_ROLE_GO ; 
 int REG_DUAL_TSF_RST ; 
 int /*<<< orphan*/  REG_TSFTR ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct p2p_ps_offload_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8723e_fill_h2c_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  rtl8723e_set_p2p_ctw_period_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 

void rtl8723e_set_p2p_ps_offload_cmd(struct ieee80211_hw *hw, u8 p2p_ps_state)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *rtlps = rtl_psc(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_p2p_ps_info *p2pinfo = &(rtlps->p2p_ps_info);
	struct p2p_ps_offload_t *p2p_ps_offload = &rtlhal->p2p_ps_offload;
	u8	i;
	u16	ctwindow;
	u32	start_time, tsf_low;

	switch (p2p_ps_state) {
	case P2P_PS_DISABLE:
		RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_DISABLE\n");
		memset(p2p_ps_offload, 0, sizeof(*p2p_ps_offload));
		break;
	case P2P_PS_ENABLE:
		RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_ENABLE\n");
		/* update CTWindow value. */
		if (p2pinfo->ctwindow > 0) {
			p2p_ps_offload->ctwindow_en = 1;
			ctwindow = p2pinfo->ctwindow;
			rtl8723e_set_p2p_ctw_period_cmd(hw, ctwindow);
		}

		/* hw only support 2 set of NoA */
		for (i = 0 ; i < p2pinfo->noa_num ; i++) {
			/* To control the register setting for which NOA*/
			rtl_write_byte(rtlpriv, 0x5cf, (i << 4));
			if (i == 0)
				p2p_ps_offload->noa0_en = 1;
			else
				p2p_ps_offload->noa1_en = 1;

			/* config P2P NoA Descriptor Register */
			rtl_write_dword(rtlpriv, 0x5E0,
					p2pinfo->noa_duration[i]);
			rtl_write_dword(rtlpriv, 0x5E4,
					p2pinfo->noa_interval[i]);

			/*Get Current TSF value */
			tsf_low = rtl_read_dword(rtlpriv, REG_TSFTR);

			start_time = p2pinfo->noa_start_time[i];
			if (p2pinfo->noa_count_type[i] != 1) {
				while (start_time <=
					(tsf_low+(50*1024))) {
					start_time +=
						p2pinfo->noa_interval[i];
					if (p2pinfo->noa_count_type[i] != 255)
						p2pinfo->noa_count_type[i]--;
				}
			}
			rtl_write_dword(rtlpriv, 0x5E8, start_time);
			rtl_write_dword(rtlpriv, 0x5EC,
				p2pinfo->noa_count_type[i]);

		}

		if ((p2pinfo->opp_ps == 1) || (p2pinfo->noa_num > 0)) {
			/* rst p2p circuit */
			rtl_write_byte(rtlpriv, REG_DUAL_TSF_RST, BIT(4));

			p2p_ps_offload->offload_en = 1;

			if (P2P_ROLE_GO == rtlpriv->mac80211.p2p) {
				p2p_ps_offload->role = 1;
				p2p_ps_offload->allstasleep = 0;
			} else {
				p2p_ps_offload->role = 0;
			}

			p2p_ps_offload->discovery = 0;
		}
		break;
	case P2P_PS_SCAN:
		RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_SCAN\n");
		p2p_ps_offload->discovery = 1;
		break;
	case P2P_PS_SCAN_DONE:
		RT_TRACE(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_SCAN_DONE\n");
		p2p_ps_offload->discovery = 0;
		p2pinfo->p2p_ps_state = P2P_PS_ENABLE;
		break;
	default:
		break;
	}

	rtl8723e_fill_h2c_cmd(hw, H2C_P2P_PS_OFFLOAD, 1, (u8 *)p2p_ps_offload);

}