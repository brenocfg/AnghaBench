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
typedef  int u16 ;
struct rtl8xxxu_txdesc32 {int /*<<< orphan*/  csum; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8xxxu_calc_tx_desc_csum(struct rtl8xxxu_txdesc32 *tx_desc)
{
	__le16 *ptr = (__le16 *)tx_desc;
	u16 csum = 0;
	int i;

	/*
	 * Clear csum field before calculation, as the csum field is
	 * in the middle of the struct.
	 */
	tx_desc->csum = cpu_to_le16(0);

	for (i = 0; i < (sizeof(struct rtl8xxxu_txdesc32) / sizeof(u16)); i++)
		csum = csum ^ le16_to_cpu(ptr[i]);

	tx_desc->csum |= cpu_to_le16(csum);
}