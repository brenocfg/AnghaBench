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
struct rtl8169_private {scalar_t__ mac_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYstatus ; 
 scalar_t__ RTL_GIGA_MAC_VER_01 ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int TBI_Enable ; 

__attribute__((used)) static bool rtl_tbi_enabled(struct rtl8169_private *tp)
{
	return (tp->mac_version == RTL_GIGA_MAC_VER_01) &&
	       (RTL_R8(tp, PHYstatus) & TBI_Enable);
}