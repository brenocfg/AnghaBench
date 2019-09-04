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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EDCA_BE_PARAM ; 
 int /*<<< orphan*/  REG_EDCA_BK_PARAM ; 
 int /*<<< orphan*/  REG_EDCA_VI_PARAM ; 
 int /*<<< orphan*/  REG_EDCA_VO_PARAM ; 
 int /*<<< orphan*/  REG_MAC_SPEC_SIFS ; 
 int /*<<< orphan*/  REG_SIFS_CTX ; 
 int /*<<< orphan*/  REG_SIFS_TRX ; 
 int /*<<< orphan*/  REG_SPEC_SIFS ; 
 int /*<<< orphan*/  rtw_write16 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _InitEDCA(struct adapter *padapter)
{
	/*  Set Spec SIFS (used in NAV) */
	rtw_write16(padapter, REG_SPEC_SIFS, 0x100a);
	rtw_write16(padapter, REG_MAC_SPEC_SIFS, 0x100a);

	/*  Set SIFS for CCK */
	rtw_write16(padapter, REG_SIFS_CTX, 0x100a);

	/*  Set SIFS for OFDM */
	rtw_write16(padapter, REG_SIFS_TRX, 0x100a);

	/*  TXOP */
	rtw_write32(padapter, REG_EDCA_BE_PARAM, 0x005EA42B);
	rtw_write32(padapter, REG_EDCA_BK_PARAM, 0x0000A44F);
	rtw_write32(padapter, REG_EDCA_VI_PARAM, 0x005EA324);
	rtw_write32(padapter, REG_EDCA_VO_PARAM, 0x002FA226);
}