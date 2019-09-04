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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl8169_private {int mac_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RTL_GIGA_MAC_VER_27 133 
#define  RTL_GIGA_MAC_VER_28 132 
#define  RTL_GIGA_MAC_VER_31 131 
#define  RTL_GIGA_MAC_VER_49 130 
#define  RTL_GIGA_MAC_VER_50 129 
#define  RTL_GIGA_MAC_VER_51 128 
 int /*<<< orphan*/  r8168dp_ocp_write (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8168ep_ocp_write (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocp_write(struct rtl8169_private *tp, u8 mask, u16 reg, u32 data)
{
	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_27:
	case RTL_GIGA_MAC_VER_28:
	case RTL_GIGA_MAC_VER_31:
		r8168dp_ocp_write(tp, mask, reg, data);
		break;
	case RTL_GIGA_MAC_VER_49:
	case RTL_GIGA_MAC_VER_50:
	case RTL_GIGA_MAC_VER_51:
		r8168ep_ocp_write(tp, mask, reg, data);
		break;
	default:
		BUG();
		break;
	}
}