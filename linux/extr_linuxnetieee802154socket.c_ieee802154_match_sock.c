#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mode; scalar_t__ extended_addr; scalar_t__ pan_id; scalar_t__ short_addr; } ;
struct dgram_sock {TYPE_1__ src_addr; int /*<<< orphan*/  bound; } ;
typedef  scalar_t__ __le64 ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 scalar_t__ IEEE802154_ADDR_LONG ; 
 scalar_t__ IEEE802154_ADDR_SHORT ; 

__attribute__((used)) static inline bool
ieee802154_match_sock(__le64 hw_addr, __le16 pan_id, __le16 short_addr,
		      struct dgram_sock *ro)
{
	if (!ro->bound)
		return true;

	if (ro->src_addr.mode == IEEE802154_ADDR_LONG &&
	    hw_addr == ro->src_addr.extended_addr)
		return true;

	if (ro->src_addr.mode == IEEE802154_ADDR_SHORT &&
	    pan_id == ro->src_addr.pan_id &&
	    short_addr == ro->src_addr.short_addr)
		return true;

	return false;
}