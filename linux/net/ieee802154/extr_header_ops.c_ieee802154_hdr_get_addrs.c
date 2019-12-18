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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  pan_id; } ;
struct TYPE_3__ {int intra_pan; int /*<<< orphan*/  source_addr_mode; int /*<<< orphan*/  dest_addr_mode; } ;
struct ieee802154_hdr {TYPE_2__ dest; TYPE_2__ source; TYPE_1__ fc; } ;

/* Variables and functions */
 scalar_t__ ieee802154_hdr_get_addr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static int
ieee802154_hdr_get_addrs(const u8 *buf, struct ieee802154_hdr *hdr)
{
	int pos = 0;

	pos += ieee802154_hdr_get_addr(buf + pos, hdr->fc.dest_addr_mode,
				       false, &hdr->dest);
	pos += ieee802154_hdr_get_addr(buf + pos, hdr->fc.source_addr_mode,
				       hdr->fc.intra_pan, &hdr->source);

	if (hdr->fc.intra_pan)
		hdr->source.pan_id = hdr->dest.pan_id;

	return pos;
}