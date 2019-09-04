#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bswenc; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  ra; } ;
struct xmit_frame {int /*<<< orphan*/  pkt; TYPE_3__ attrib; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* mgnt_xmit ) (struct adapter*,struct xmit_frame*) ;} ;
struct TYPE_5__ {int binstallBIPkey; } ;
struct adapter {TYPE_1__ HalFunc; TYPE_2__ securitypriv; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ IS_MCAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _AES_ ; 
 int /*<<< orphan*/  _BIP_ ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  rtw_mgmt_xmitframe_coalesce (struct adapter*,int /*<<< orphan*/ ,struct xmit_frame*) ; 
 int /*<<< orphan*/  stub1 (struct adapter*,struct xmit_frame*) ; 
 int /*<<< orphan*/  update_mgntframe_attrib_addr (struct adapter*,struct xmit_frame*) ; 

s32	rtw_hal_mgnt_xmit(struct adapter *padapter, struct xmit_frame *pmgntframe)
{
	s32 ret = _FAIL;
	update_mgntframe_attrib_addr(padapter, pmgntframe);
	/* pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET; */
	/* pwlanhdr = (struct rtw_ieee80211_hdr *)pframe; */
	/* memcpy(pmgntframe->attrib.ra, pwlanhdr->addr1, ETH_ALEN); */

	if (padapter->securitypriv.binstallBIPkey == true) {
		if (IS_MCAST(pmgntframe->attrib.ra)) {
			pmgntframe->attrib.encrypt = _BIP_;
			/* pmgntframe->attrib.bswenc = true; */
		} else {
			pmgntframe->attrib.encrypt = _AES_;
			pmgntframe->attrib.bswenc = true;
		}
		rtw_mgmt_xmitframe_coalesce(padapter, pmgntframe->pkt, pmgntframe);
	}

	if (padapter->HalFunc.mgnt_xmit)
		ret = padapter->HalFunc.mgnt_xmit(padapter, pmgntframe);
	return ret;
}