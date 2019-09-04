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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RATE_BITMAP_ALL ; 
 int /*<<< orphan*/  RATE_RRSR_CCK_ONLY_1M ; 
 int /*<<< orphan*/  REG_RL ; 
 int /*<<< orphan*/  REG_RRSR ; 
 int /*<<< orphan*/  REG_SPEC_SIFS ; 
 int _LRL (int) ; 
 int _SPEC_SIFS_CCK (int) ; 
 int _SPEC_SIFS_OFDM (int) ; 
 int _SRL (int) ; 
 int /*<<< orphan*/  usb_read32 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_write16 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_write32 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _InitAdaptiveCtrl(struct adapter *Adapter)
{
	u16 value16;
	u32 value32;

	/*  Response Rate Set */
	value32 = usb_read32(Adapter, REG_RRSR);
	value32 &= ~RATE_BITMAP_ALL;
	value32 |= RATE_RRSR_CCK_ONLY_1M;
	usb_write32(Adapter, REG_RRSR, value32);

	/*  CF-END Threshold */

	/*  SIFS (used in NAV) */
	value16 = _SPEC_SIFS_CCK(0x10) | _SPEC_SIFS_OFDM(0x10);
	usb_write16(Adapter, REG_SPEC_SIFS, value16);

	/*  Retry Limit */
	value16 = _LRL(0x30) | _SRL(0x30);
	usb_write16(Adapter, REG_RL, value16);
}