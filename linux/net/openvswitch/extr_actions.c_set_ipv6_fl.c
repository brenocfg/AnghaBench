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
typedef  int u32 ;
struct ipv6hdr {int /*<<< orphan*/ * flow_lbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVS_SET_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_ipv6_fl(struct ipv6hdr *nh, u32 fl, u32 mask)
{
	/* Bits 21-24 are always unmasked, so this retains their values. */
	OVS_SET_MASKED(nh->flow_lbl[0], (u8)(fl >> 16), (u8)(mask >> 16));
	OVS_SET_MASKED(nh->flow_lbl[1], (u8)(fl >> 8), (u8)(mask >> 8));
	OVS_SET_MASKED(nh->flow_lbl[2], (u8)fl, (u8)mask);
}