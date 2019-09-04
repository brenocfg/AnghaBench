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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int MT_EE_NIC_CONF_1 ; 
 int MT_EE_NIC_CONF_1_TX_ALC_EN ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
mt7601u_has_tssi(struct mt7601u_dev *dev, u8 *eeprom)
{
	u16 nic_conf1 = get_unaligned_le16(eeprom + MT_EE_NIC_CONF_1);

	return ~nic_conf1 && (nic_conf1 & MT_EE_NIC_CONF_1_TX_ALC_EN);
}