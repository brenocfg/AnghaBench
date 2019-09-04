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
struct rt2x00_dev {int dummy; } ;
struct antenna_setup {int rx; int tx; } ;

/* Variables and functions */
#define  ANTENNA_A 130 
#define  ANTENNA_B 129 
#define  ANTENNA_HW_DIVERSITY 128 
 int ANTENNA_SW_DIVERSITY ; 
 int /*<<< orphan*/  BBP_R1_TX_ANTENNA ; 
 int /*<<< orphan*/  BBP_R4_RX_ANTENNA ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  rt2400pci_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2400pci_bbp_write (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2400pci_config_ant(struct rt2x00_dev *rt2x00dev,
				 struct antenna_setup *ant)
{
	u8 r1;
	u8 r4;

	/*
	 * We should never come here because rt2x00lib is supposed
	 * to catch this and send us the correct antenna explicitely.
	 */
	BUG_ON(ant->rx == ANTENNA_SW_DIVERSITY ||
	       ant->tx == ANTENNA_SW_DIVERSITY);

	r4 = rt2400pci_bbp_read(rt2x00dev, 4);
	r1 = rt2400pci_bbp_read(rt2x00dev, 1);

	/*
	 * Configure the TX antenna.
	 */
	switch (ant->tx) {
	case ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r1, BBP_R1_TX_ANTENNA, 1);
		break;
	case ANTENNA_A:
		rt2x00_set_field8(&r1, BBP_R1_TX_ANTENNA, 0);
		break;
	case ANTENNA_B:
	default:
		rt2x00_set_field8(&r1, BBP_R1_TX_ANTENNA, 2);
		break;
	}

	/*
	 * Configure the RX antenna.
	 */
	switch (ant->rx) {
	case ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA, 1);
		break;
	case ANTENNA_A:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA, 0);
		break;
	case ANTENNA_B:
	default:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA, 2);
		break;
	}

	rt2400pci_bbp_write(rt2x00dev, 4, r4);
	rt2400pci_bbp_write(rt2x00dev, 1, r1);
}