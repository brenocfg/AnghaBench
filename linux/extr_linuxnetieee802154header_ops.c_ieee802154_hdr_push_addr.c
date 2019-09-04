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
struct ieee802154_addr {int mode; int /*<<< orphan*/  extended_addr; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  pan_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE802154_ADDR_LEN ; 
#define  IEEE802154_ADDR_LONG 129 
 int IEEE802154_ADDR_NONE ; 
#define  IEEE802154_ADDR_SHORT 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ieee802154_hdr_push_addr(u8 *buf, const struct ieee802154_addr *addr,
			 bool omit_pan)
{
	int pos = 0;

	if (addr->mode == IEEE802154_ADDR_NONE)
		return 0;

	if (!omit_pan) {
		memcpy(buf + pos, &addr->pan_id, 2);
		pos += 2;
	}

	switch (addr->mode) {
	case IEEE802154_ADDR_SHORT:
		memcpy(buf + pos, &addr->short_addr, 2);
		pos += 2;
		break;

	case IEEE802154_ADDR_LONG:
		memcpy(buf + pos, &addr->extended_addr, IEEE802154_ADDR_LEN);
		pos += IEEE802154_ADDR_LEN;
		break;

	default:
		return -EINVAL;
	}

	return pos;
}