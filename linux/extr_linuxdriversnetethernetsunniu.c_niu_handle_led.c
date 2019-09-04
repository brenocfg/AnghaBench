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
 int NIU_FLAGS_10G ; 
 int NIU_FLAGS_FIBER ; 
 int /*<<< orphan*/  XMAC_CONFIG ; 
 int /*<<< orphan*/  XMAC_CONFIG_FORCE_LED_ON ; 
 int /*<<< orphan*/  XMAC_CONFIG_LED_POLARITY ; 
 int /*<<< orphan*/  nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_handle_led(struct niu *np, int status)
{
	u64 val;
	val = nr64_mac(XMAC_CONFIG);

	if ((np->flags & NIU_FLAGS_10G) != 0 &&
	    (np->flags & NIU_FLAGS_FIBER) != 0) {
		if (status) {
			val |= XMAC_CONFIG_LED_POLARITY;
			val &= ~XMAC_CONFIG_FORCE_LED_ON;
		} else {
			val |= XMAC_CONFIG_FORCE_LED_ON;
			val &= ~XMAC_CONFIG_LED_POLARITY;
		}
	}

	nw64_mac(XMAC_CONFIG, val);
}