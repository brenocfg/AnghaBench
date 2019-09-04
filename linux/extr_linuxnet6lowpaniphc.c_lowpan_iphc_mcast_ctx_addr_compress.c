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
struct lowpan_iphc_ctx {int dummy; } ;
struct in6_addr {int /*<<< orphan*/ * s6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOWPAN_IPHC_DAM_00 ; 
 int /*<<< orphan*/  lowpan_push_hc_data (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u8 lowpan_iphc_mcast_ctx_addr_compress(u8 **hc_ptr,
					      const struct lowpan_iphc_ctx *ctx,
					      const struct in6_addr *ipaddr)
{
	u8 data[6];

	/* flags/scope, reserved (RIID) */
	memcpy(data, &ipaddr->s6_addr[1], 2);
	/* group ID */
	memcpy(&data[1], &ipaddr->s6_addr[11], 4);
	lowpan_push_hc_data(hc_ptr, data, 6);

	return LOWPAN_IPHC_DAM_00;
}