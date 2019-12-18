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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  OVS_SET_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void ether_addr_copy_masked(u8 *dst_, const u8 *src_, const u8 *mask_)
{
	u16 *dst = (u16 *)dst_;
	const u16 *src = (const u16 *)src_;
	const u16 *mask = (const u16 *)mask_;

	OVS_SET_MASKED(dst[0], src[0], mask[0]);
	OVS_SET_MASKED(dst[1], src[1], mask[1]);
	OVS_SET_MASKED(dst[2], src[2], mask[2]);
}