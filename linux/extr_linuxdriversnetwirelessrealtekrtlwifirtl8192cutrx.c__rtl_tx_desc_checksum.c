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
typedef  int u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  SET_TX_DESC_TX_DESC_CHECKSUM (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl_tx_desc_checksum(u8 *txdesc)
{
	__le16 *ptr = (__le16 *)txdesc;
	u16	checksum = 0;
	u32 index;

	/* Clear first */
	SET_TX_DESC_TX_DESC_CHECKSUM(txdesc, 0);
	for (index = 0; index < 16; index++)
		checksum = checksum ^ le16_to_cpu(*(ptr + index));
	SET_TX_DESC_TX_DESC_CHECKSUM(txdesc, checksum);
}