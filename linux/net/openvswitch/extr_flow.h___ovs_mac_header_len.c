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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 scalar_t__ MAC_PROTO_ETHERNET ; 

__attribute__((used)) static inline u16 __ovs_mac_header_len(u8 mac_proto)
{
	return mac_proto == MAC_PROTO_ETHERNET ? ETH_HLEN : 0;
}