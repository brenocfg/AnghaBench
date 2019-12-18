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
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int IEEE802154_ADDR_UNDEF ; 
 scalar_t__ cpu_to_le16 (int) ; 

__attribute__((used)) static bool llsec_dev_use_shortaddr(__le16 short_addr)
{
	return short_addr != cpu_to_le16(IEEE802154_ADDR_UNDEF) &&
		short_addr != cpu_to_le16(0xffff);
}