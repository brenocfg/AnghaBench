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
 int /*<<< orphan*/  usb_write16 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _InitEDCA(struct adapter *Adapter)
{
	/*  Set Spec SIFS (used in NAV) */
	usb_write16(Adapter, REG_SPEC_SIFS, 0x100a);
	usb_write16(Adapter, REG_MAC_SPEC_SIFS, 0x100a);

	/*  Set SIFS for CCK */
	usb_write16(Adapter, REG_SIFS_CTX, 0x100a);

	/*  Set SIFS for OFDM */
	usb_write16(Adapter, REG_SIFS_TRX, 0x100a);

	/*  TXOP */
	usb_write32(Adapter, REG_EDCA_BE_PARAM, 0x005EA42B);
	usb_write32(Adapter, REG_EDCA_BK_PARAM, 0x0000A44F);
	usb_write32(Adapter, REG_EDCA_VI_PARAM, 0x005EA324);
	usb_write32(Adapter, REG_EDCA_VO_PARAM, 0x002FA226);
}