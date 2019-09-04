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
struct TYPE_2__ {int flags; scalar_t__ enabled; } ;
struct batadv_priv {TYPE_1__ mcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_MCAST ; 
 int BATADV_MCAST_WANT_ALL_IPV4 ; 
 int BATADV_MCAST_WANT_ALL_IPV6 ; 
 int BATADV_MCAST_WANT_ALL_UNSNOOPABLES ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,char*,unsigned char,char,char) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char,char,char) ; 

__attribute__((used)) static void batadv_mcast_flags_log(struct batadv_priv *bat_priv, u8 flags)
{
	u8 old_flags = bat_priv->mcast.flags;
	char str_old_flags[] = "[...]";

	sprintf(str_old_flags, "[%c%c%c]",
		(old_flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES) ? 'U' : '.',
		(old_flags & BATADV_MCAST_WANT_ALL_IPV4) ? '4' : '.',
		(old_flags & BATADV_MCAST_WANT_ALL_IPV6) ? '6' : '.');

	batadv_dbg(BATADV_DBG_MCAST, bat_priv,
		   "Changing multicast flags from '%s' to '[%c%c%c]'\n",
		   bat_priv->mcast.enabled ? str_old_flags : "<undefined>",
		   (flags & BATADV_MCAST_WANT_ALL_UNSNOOPABLES) ? 'U' : '.',
		   (flags & BATADV_MCAST_WANT_ALL_IPV4) ? '4' : '.',
		   (flags & BATADV_MCAST_WANT_ALL_IPV6) ? '6' : '.');
}