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
typedef  int u32 ;
struct rt2x00lib_erp {int short_preamble; int basic_rates; int slot_time; int sifs; int pifs; int difs; int eifs; int beacon_int; } ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_SIZE ; 
 int /*<<< orphan*/  ARCSR1 ; 
 int /*<<< orphan*/  ARCSR2 ; 
 int /*<<< orphan*/  ARCSR2_LENGTH ; 
 int /*<<< orphan*/  ARCSR2_SERVICE ; 
 int /*<<< orphan*/  ARCSR2_SIGNAL ; 
 int /*<<< orphan*/  ARCSR3 ; 
 int /*<<< orphan*/  ARCSR3_SERVICE ; 
 int /*<<< orphan*/  ARCSR3_SIGNAL ; 
 int /*<<< orphan*/  ARCSR4 ; 
 int /*<<< orphan*/  ARCSR4_SERVICE ; 
 int /*<<< orphan*/  ARCSR4_SIGNAL ; 
 int /*<<< orphan*/  ARCSR5 ; 
 int /*<<< orphan*/  ARCSR5_SERVICE ; 
 int /*<<< orphan*/  ARCSR5_SIGNAL ; 
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int /*<<< orphan*/  CSR11 ; 
 int /*<<< orphan*/  CSR11_SLOT_TIME ; 
 int /*<<< orphan*/  CSR12 ; 
 int /*<<< orphan*/  CSR12_BEACON_INTERVAL ; 
 int /*<<< orphan*/  CSR12_CFP_MAX_DURATION ; 
 int /*<<< orphan*/  CSR18 ; 
 int /*<<< orphan*/  CSR18_PIFS ; 
 int /*<<< orphan*/  CSR18_SIFS ; 
 int /*<<< orphan*/  CSR19 ; 
 int /*<<< orphan*/  CSR19_DIFS ; 
 int /*<<< orphan*/  CSR19_EIFS ; 
 int GET_DURATION (int /*<<< orphan*/ ,int) ; 
 int IEEE80211_HEADER ; 
 int /*<<< orphan*/  TXCSR1 ; 
 int /*<<< orphan*/  TXCSR1_ACK_CONSUME_TIME ; 
 int /*<<< orphan*/  TXCSR1_ACK_TIMEOUT ; 
 int /*<<< orphan*/  TXCSR1_AUTORESPONDER ; 
 int /*<<< orphan*/  TXCSR1_TSF_OFFSET ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2400pci_config_erp(struct rt2x00_dev *rt2x00dev,
				 struct rt2x00lib_erp *erp,
				 u32 changed)
{
	int preamble_mask;
	u32 reg;

	/*
	 * When short preamble is enabled, we should set bit 0x08
	 */
	if (changed & BSS_CHANGED_ERP_PREAMBLE) {
		preamble_mask = erp->short_preamble << 3;

		reg = rt2x00mmio_register_read(rt2x00dev, TXCSR1);
		rt2x00_set_field32(&reg, TXCSR1_ACK_TIMEOUT, 0x1ff);
		rt2x00_set_field32(&reg, TXCSR1_ACK_CONSUME_TIME, 0x13a);
		rt2x00_set_field32(&reg, TXCSR1_TSF_OFFSET, IEEE80211_HEADER);
		rt2x00_set_field32(&reg, TXCSR1_AUTORESPONDER, 1);
		rt2x00mmio_register_write(rt2x00dev, TXCSR1, reg);

		reg = rt2x00mmio_register_read(rt2x00dev, ARCSR2);
		rt2x00_set_field32(&reg, ARCSR2_SIGNAL, 0x00);
		rt2x00_set_field32(&reg, ARCSR2_SERVICE, 0x04);
		rt2x00_set_field32(&reg, ARCSR2_LENGTH,
				   GET_DURATION(ACK_SIZE, 10));
		rt2x00mmio_register_write(rt2x00dev, ARCSR2, reg);

		reg = rt2x00mmio_register_read(rt2x00dev, ARCSR3);
		rt2x00_set_field32(&reg, ARCSR3_SIGNAL, 0x01 | preamble_mask);
		rt2x00_set_field32(&reg, ARCSR3_SERVICE, 0x04);
		rt2x00_set_field32(&reg, ARCSR2_LENGTH,
				   GET_DURATION(ACK_SIZE, 20));
		rt2x00mmio_register_write(rt2x00dev, ARCSR3, reg);

		reg = rt2x00mmio_register_read(rt2x00dev, ARCSR4);
		rt2x00_set_field32(&reg, ARCSR4_SIGNAL, 0x02 | preamble_mask);
		rt2x00_set_field32(&reg, ARCSR4_SERVICE, 0x04);
		rt2x00_set_field32(&reg, ARCSR2_LENGTH,
				   GET_DURATION(ACK_SIZE, 55));
		rt2x00mmio_register_write(rt2x00dev, ARCSR4, reg);

		reg = rt2x00mmio_register_read(rt2x00dev, ARCSR5);
		rt2x00_set_field32(&reg, ARCSR5_SIGNAL, 0x03 | preamble_mask);
		rt2x00_set_field32(&reg, ARCSR5_SERVICE, 0x84);
		rt2x00_set_field32(&reg, ARCSR2_LENGTH,
				   GET_DURATION(ACK_SIZE, 110));
		rt2x00mmio_register_write(rt2x00dev, ARCSR5, reg);
	}

	if (changed & BSS_CHANGED_BASIC_RATES)
		rt2x00mmio_register_write(rt2x00dev, ARCSR1, erp->basic_rates);

	if (changed & BSS_CHANGED_ERP_SLOT) {
		reg = rt2x00mmio_register_read(rt2x00dev, CSR11);
		rt2x00_set_field32(&reg, CSR11_SLOT_TIME, erp->slot_time);
		rt2x00mmio_register_write(rt2x00dev, CSR11, reg);

		reg = rt2x00mmio_register_read(rt2x00dev, CSR18);
		rt2x00_set_field32(&reg, CSR18_SIFS, erp->sifs);
		rt2x00_set_field32(&reg, CSR18_PIFS, erp->pifs);
		rt2x00mmio_register_write(rt2x00dev, CSR18, reg);

		reg = rt2x00mmio_register_read(rt2x00dev, CSR19);
		rt2x00_set_field32(&reg, CSR19_DIFS, erp->difs);
		rt2x00_set_field32(&reg, CSR19_EIFS, erp->eifs);
		rt2x00mmio_register_write(rt2x00dev, CSR19, reg);
	}

	if (changed & BSS_CHANGED_BEACON_INT) {
		reg = rt2x00mmio_register_read(rt2x00dev, CSR12);
		rt2x00_set_field32(&reg, CSR12_BEACON_INTERVAL,
				   erp->beacon_int * 16);
		rt2x00_set_field32(&reg, CSR12_CFP_MAX_DURATION,
				   erp->beacon_int * 16);
		rt2x00mmio_register_write(rt2x00dev, CSR12, reg);
	}
}