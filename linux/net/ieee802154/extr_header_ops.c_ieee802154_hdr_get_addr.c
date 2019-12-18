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
 int IEEE802154_ADDR_LEN ; 
 int IEEE802154_ADDR_NONE ; 
 int IEEE802154_ADDR_SHORT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
ieee802154_hdr_get_addr(const u8 *buf, int mode, bool omit_pan,
			struct ieee802154_addr *addr)
{
	int pos = 0;

	addr->mode = mode;

	if (mode == IEEE802154_ADDR_NONE)
		return 0;

	if (!omit_pan) {
		memcpy(&addr->pan_id, buf + pos, 2);
		pos += 2;
	}

	if (mode == IEEE802154_ADDR_SHORT) {
		memcpy(&addr->short_addr, buf + pos, 2);
		return pos + 2;
	} else {
		memcpy(&addr->extended_addr, buf + pos, IEEE802154_ADDR_LEN);
		return pos + IEEE802154_ADDR_LEN;
	}
}