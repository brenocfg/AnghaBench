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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int device; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned char BIT (unsigned char) ; 
 int /*<<< orphan*/  PT1_P1_REG ; 
 int /*<<< orphan*/  PT1_P2_REG ; 
 int /*<<< orphan*/  PT2_P1_REG ; 
 int /*<<< orphan*/  PT2_P2_REG ; 
 int /*<<< orphan*/  PT4_P1_REG ; 
 int /*<<< orphan*/  PT4_P2_REG ; 
 int /*<<< orphan*/  PT_ADDR_INDX ; 
 int /*<<< orphan*/  PT_READ_INDX ; 
 int /*<<< orphan*/  PT_SIG_1_ADDR ; 
 unsigned char PT_SIG_1_DATA ; 
 int /*<<< orphan*/  PT_SIG_2_ADDR ; 
 unsigned char PT_SIG_2_DATA ; 
 int /*<<< orphan*/  PT_SIG_3_ADDR ; 
 unsigned char PT_SIG_3_DATA ; 
 int /*<<< orphan*/  PT_SIG_4_ADDR ; 
 unsigned char PT_SIG_4_DATA ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

bool usb_amd_pt_check_port(struct device *device, int port)
{
	unsigned char value, port_shift;
	struct pci_dev *pdev;
	u16 reg;

	pdev = to_pci_dev(device);
	pci_write_config_word(pdev, PT_ADDR_INDX, PT_SIG_1_ADDR);

	pci_read_config_byte(pdev, PT_READ_INDX, &value);
	if (value != PT_SIG_1_DATA)
		return false;

	pci_write_config_word(pdev, PT_ADDR_INDX, PT_SIG_2_ADDR);

	pci_read_config_byte(pdev, PT_READ_INDX, &value);
	if (value != PT_SIG_2_DATA)
		return false;

	pci_write_config_word(pdev, PT_ADDR_INDX, PT_SIG_3_ADDR);

	pci_read_config_byte(pdev, PT_READ_INDX, &value);
	if (value != PT_SIG_3_DATA)
		return false;

	pci_write_config_word(pdev, PT_ADDR_INDX, PT_SIG_4_ADDR);

	pci_read_config_byte(pdev, PT_READ_INDX, &value);
	if (value != PT_SIG_4_DATA)
		return false;

	/* Check disabled port setting, if bit is set port is enabled */
	switch (pdev->device) {
	case 0x43b9:
	case 0x43ba:
	/*
	 * device is AMD_PROMONTORYA_4(0x43b9) or PROMONTORYA_3(0x43ba)
	 * PT4_P1_REG bits[7..1] represents USB2.0 ports 6 to 0
	 * PT4_P2_REG bits[6..0] represents ports 13 to 7
	 */
		if (port > 6) {
			reg = PT4_P2_REG;
			port_shift = port - 7;
		} else {
			reg = PT4_P1_REG;
			port_shift = port + 1;
		}
		break;
	case 0x43bb:
	/*
	 * device is AMD_PROMONTORYA_2(0x43bb)
	 * PT2_P1_REG bits[7..5] represents USB2.0 ports 2 to 0
	 * PT2_P2_REG bits[5..0] represents ports 9 to 3
	 */
		if (port > 2) {
			reg = PT2_P2_REG;
			port_shift = port - 3;
		} else {
			reg = PT2_P1_REG;
			port_shift = port + 5;
		}
		break;
	case 0x43bc:
	/*
	 * device is AMD_PROMONTORYA_1(0x43bc)
	 * PT1_P1_REG[7..4] represents USB2.0 ports 3 to 0
	 * PT1_P2_REG[5..0] represents ports 9 to 4
	 */
		if (port > 3) {
			reg = PT1_P2_REG;
			port_shift = port - 4;
		} else {
			reg = PT1_P1_REG;
			port_shift = port + 4;
		}
		break;
	default:
		return false;
	}
	pci_write_config_word(pdev, PT_ADDR_INDX, reg);
	pci_read_config_byte(pdev, PT_READ_INDX, &value);

	return !(value & BIT(port_shift));
}