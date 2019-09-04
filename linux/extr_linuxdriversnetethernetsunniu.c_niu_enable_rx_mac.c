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
struct niu {int flags; } ;

/* Variables and functions */
 int NIU_FLAGS_XMAC ; 
 int /*<<< orphan*/  niu_enable_rx_bmac (struct niu*,int) ; 
 int /*<<< orphan*/  niu_enable_rx_xmac (struct niu*,int) ; 

__attribute__((used)) static void niu_enable_rx_mac(struct niu *np, int on)
{
	if (np->flags & NIU_FLAGS_XMAC)
		niu_enable_rx_xmac(np, on);
	else
		niu_enable_rx_bmac(np, on);
}