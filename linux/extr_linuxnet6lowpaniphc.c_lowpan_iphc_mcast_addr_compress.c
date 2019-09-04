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
struct in6_addr {int /*<<< orphan*/ * s6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOWPAN_IPHC_DAM_00 ; 
 int /*<<< orphan*/  LOWPAN_IPHC_DAM_01 ; 
 int /*<<< orphan*/  LOWPAN_IPHC_DAM_10 ; 
 int /*<<< orphan*/  LOWPAN_IPHC_DAM_11 ; 
 scalar_t__ lowpan_is_mcast_addr_compressable32 (struct in6_addr const*) ; 
 scalar_t__ lowpan_is_mcast_addr_compressable48 (struct in6_addr const*) ; 
 scalar_t__ lowpan_is_mcast_addr_compressable8 (struct in6_addr const*) ; 
 int /*<<< orphan*/  lowpan_push_hc_data (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static u8 lowpan_iphc_mcast_addr_compress(u8 **hc_ptr,
					  const struct in6_addr *ipaddr)
{
	u8 val;

	if (lowpan_is_mcast_addr_compressable8(ipaddr)) {
		pr_debug("compressed to 1 octet\n");
		/* use last byte */
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[15], 1);
		val = LOWPAN_IPHC_DAM_11;
	} else if (lowpan_is_mcast_addr_compressable32(ipaddr)) {
		pr_debug("compressed to 4 octets\n");
		/* second byte + the last three */
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[1], 1);
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[13], 3);
		val = LOWPAN_IPHC_DAM_10;
	} else if (lowpan_is_mcast_addr_compressable48(ipaddr)) {
		pr_debug("compressed to 6 octets\n");
		/* second byte + the last five */
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[1], 1);
		lowpan_push_hc_data(hc_ptr, &ipaddr->s6_addr[11], 5);
		val = LOWPAN_IPHC_DAM_01;
	} else {
		pr_debug("using full address\n");
		lowpan_push_hc_data(hc_ptr, ipaddr->s6_addr, 16);
		val = LOWPAN_IPHC_DAM_00;
	}

	return val;
}