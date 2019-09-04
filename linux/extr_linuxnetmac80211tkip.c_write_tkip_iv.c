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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u8 *write_tkip_iv(u8 *pos, u16 iv16)
{
	*pos++ = iv16 >> 8;
	*pos++ = ((iv16 >> 8) | 0x20) & 0x7f;
	*pos++ = iv16 & 0xFF;
	return pos;
}