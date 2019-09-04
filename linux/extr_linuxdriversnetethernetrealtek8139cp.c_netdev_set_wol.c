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
typedef  int u8 ;
struct ethtool_wolinfo {int wolopts; } ;
struct cp_private {int wol_enabled; } ;

/* Variables and functions */
 int BWF ; 
 int /*<<< orphan*/  Cfg9346 ; 
 int Cfg9346_Lock ; 
 int Cfg9346_Unlock ; 
 int /*<<< orphan*/  Config3 ; 
 int /*<<< orphan*/  Config5 ; 
 int LinkUp ; 
 int MWF ; 
 int MagicPacket ; 
 int UWF ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 int cpr8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int netdev_set_wol (struct cp_private *cp,
			   const struct ethtool_wolinfo *wol)
{
	u8 options;

	options = cpr8 (Config3) & ~(LinkUp | MagicPacket);
	/* If WOL is being disabled, no need for complexity */
	if (wol->wolopts) {
		if (wol->wolopts & WAKE_PHY)	options |= LinkUp;
		if (wol->wolopts & WAKE_MAGIC)	options |= MagicPacket;
	}

	cpw8 (Cfg9346, Cfg9346_Unlock);
	cpw8 (Config3, options);
	cpw8 (Cfg9346, Cfg9346_Lock);

	options = 0; /* Paranoia setting */
	options = cpr8 (Config5) & ~(UWF | MWF | BWF);
	/* If WOL is being disabled, no need for complexity */
	if (wol->wolopts) {
		if (wol->wolopts & WAKE_UCAST)  options |= UWF;
		if (wol->wolopts & WAKE_BCAST)	options |= BWF;
		if (wol->wolopts & WAKE_MCAST)	options |= MWF;
	}

	cpw8 (Config5, options);

	cp->wol_enabled = (wol->wolopts) ? 1 : 0;

	return 0;
}