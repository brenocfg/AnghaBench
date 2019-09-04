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
struct ieee802154_llsec_key_id {int mode; scalar_t__ id; int /*<<< orphan*/  extended_source; int /*<<< orphan*/  short_source; int /*<<< orphan*/  device_addr; } ;

/* Variables and functions */
#define  IEEE802154_SCF_KEY_HW_INDEX 130 
 int IEEE802154_SCF_KEY_IMPLICIT ; 
#define  IEEE802154_SCF_KEY_INDEX 129 
#define  IEEE802154_SCF_KEY_SHORT_INDEX 128 
 int ieee802154_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool llsec_key_id_equal(const struct ieee802154_llsec_key_id *a,
			       const struct ieee802154_llsec_key_id *b)
{
	if (a->mode != b->mode)
		return false;

	if (a->mode == IEEE802154_SCF_KEY_IMPLICIT)
		return ieee802154_addr_equal(&a->device_addr, &b->device_addr);

	if (a->id != b->id)
		return false;

	switch (a->mode) {
	case IEEE802154_SCF_KEY_INDEX:
		return true;
	case IEEE802154_SCF_KEY_SHORT_INDEX:
		return a->short_source == b->short_source;
	case IEEE802154_SCF_KEY_HW_INDEX:
		return a->extended_source == b->extended_source;
	}

	return false;
}