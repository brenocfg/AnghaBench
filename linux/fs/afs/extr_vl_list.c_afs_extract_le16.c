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

__attribute__((used)) static u16 afs_extract_le16(const u8 **_b)
{
	u16 val;

	val  = (u16)*(*_b)++ << 0;
	val |= (u16)*(*_b)++ << 8;
	return val;
}