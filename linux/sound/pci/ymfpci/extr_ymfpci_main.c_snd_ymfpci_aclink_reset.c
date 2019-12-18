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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_DSXG_CTRL ; 
 int /*<<< orphan*/  PCIR_DSXG_PWRCTRL1 ; 
 int /*<<< orphan*/  PCIR_DSXG_PWRCTRL2 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ymfpci_aclink_reset(struct pci_dev * pci)
{
	u8 cmd;

	pci_read_config_byte(pci, PCIR_DSXG_CTRL, &cmd);
#if 0 // force to reset
	if (cmd & 0x03) {
#endif
		pci_write_config_byte(pci, PCIR_DSXG_CTRL, cmd & 0xfc);
		pci_write_config_byte(pci, PCIR_DSXG_CTRL, cmd | 0x03);
		pci_write_config_byte(pci, PCIR_DSXG_CTRL, cmd & 0xfc);
		pci_write_config_word(pci, PCIR_DSXG_PWRCTRL1, 0);
		pci_write_config_word(pci, PCIR_DSXG_PWRCTRL2, 0);
#if 0
	}
#endif
}