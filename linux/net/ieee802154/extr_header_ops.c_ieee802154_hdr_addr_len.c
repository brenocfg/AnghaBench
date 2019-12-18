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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE802154_ADDR_LEN ; 
#define  IEEE802154_ADDR_LONG 130 
#define  IEEE802154_ADDR_NONE 129 
#define  IEEE802154_ADDR_SHORT 128 

__attribute__((used)) static int ieee802154_hdr_addr_len(int mode, bool omit_pan)
{
	int pan_len = omit_pan ? 0 : 2;

	switch (mode) {
	case IEEE802154_ADDR_NONE: return 0;
	case IEEE802154_ADDR_SHORT: return 2 + pan_len;
	case IEEE802154_ADDR_LONG: return IEEE802154_ADDR_LEN + pan_len;
	default: return -EINVAL;
	}
}