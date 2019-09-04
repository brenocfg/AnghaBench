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
typedef  int /*<<< orphan*/  u64 ;
struct niu {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAC_XIF_CONFIG ; 
 int NIU_FLAGS_XMAC ; 
 int /*<<< orphan*/  XMAC_CONFIG ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_led_state_restore(struct niu *np, u64 val)
{
	if (np->flags & NIU_FLAGS_XMAC)
		nw64_mac(XMAC_CONFIG, val);
	else
		nw64_mac(BMAC_XIF_CONFIG, val);
}