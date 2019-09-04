#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t key_id_mode; } ;
struct TYPE_3__ {scalar_t__ security_enabled; } ;
struct ieee802154_hdr {TYPE_2__ sec; TYPE_1__ fc; } ;

/* Variables and functions */
 int IEEE802154_MFR_SIZE ; 
 int IEEE802154_MTU ; 
 int ieee802154_hdr_minlen (struct ieee802154_hdr const*) ; 
 scalar_t__ ieee802154_sechdr_authtag_len (TYPE_2__*) ; 
 int* ieee802154_sechdr_lengths ; 

int ieee802154_max_payload(const struct ieee802154_hdr *hdr)
{
	int hlen = ieee802154_hdr_minlen(hdr);

	if (hdr->fc.security_enabled) {
		hlen += ieee802154_sechdr_lengths[hdr->sec.key_id_mode] - 1;
		hlen += ieee802154_sechdr_authtag_len(&hdr->sec);
	}

	return IEEE802154_MTU - hlen - IEEE802154_MFR_SIZE;
}