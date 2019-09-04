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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct tx_desc {int /*<<< orphan*/  txdw7; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8188eu_cal_txdesc_chksum(struct tx_desc	*ptxdesc)
{
	u16 *usptr = (u16 *)ptxdesc;
	u32 count = 16; /* (32 bytes / 2 bytes per XOR) => 16 times */
	u32 index;
	u16 checksum = 0;

	/* Clear first */
	ptxdesc->txdw7 &= cpu_to_le32(0xffff0000);

	for (index = 0; index < count; index++)
		checksum = checksum ^ le16_to_cpu(*(__le16 *)(usptr + index));
	ptxdesc->txdw7 |= cpu_to_le32(0x0000ffff & checksum);
}