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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ahd_dev_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

uint32_t
ahd_pci_read_config(ahd_dev_softc_t pci, int reg, int width)
{
	switch (width) {
	case 1:
	{
		uint8_t retval;

		pci_read_config_byte(pci, reg, &retval);
		return (retval);
	}
	case 2:
	{
		uint16_t retval;
		pci_read_config_word(pci, reg, &retval);
		return (retval);
	}
	case 4:
	{
		uint32_t retval;
		pci_read_config_dword(pci, reg, &retval);
		return (retval);
	}
	default:
		panic("ahd_pci_read_config: Read size too big");
		/* NOTREACHED */
		return (0);
	}
}