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
struct l2tp_tunnel {int dummy; } ;

/* Variables and functions */
 int PPPOL2TP_HEADER_OVERHEAD ; 
 int l2tp_tunnel_dst_mtu (struct l2tp_tunnel const*) ; 

__attribute__((used)) static int pppol2tp_tunnel_mtu(const struct l2tp_tunnel *tunnel)
{
	int mtu;

	mtu = l2tp_tunnel_dst_mtu(tunnel);
	if (mtu <= PPPOL2TP_HEADER_OVERHEAD)
		return 1500 - PPPOL2TP_HEADER_OVERHEAD;

	return mtu - PPPOL2TP_HEADER_OVERHEAD;
}