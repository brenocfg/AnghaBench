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
typedef  int /*<<< orphan*/  SLMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned short) ; 
 int /*<<< orphan*/  read_status_reg (int /*<<< orphan*/ *) ; 
 unsigned short sca_pci_load_interval ; 

__attribute__((used)) static void load_pci_memory(SLMP_INFO *info, char* dest, const char* src, unsigned short count)
{
	/* A load interval of 16 allows for 4 32-bit writes at */
	/* 136ns each for a maximum latency of 542ns on the local bus.*/

	unsigned short interval = count / sca_pci_load_interval;
	unsigned short i;

	for ( i = 0 ; i < interval ; i++ )
	{
		memcpy(dest, src, sca_pci_load_interval);
		read_status_reg(info);
		dest += sca_pci_load_interval;
		src += sca_pci_load_interval;
	}

	memcpy(dest, src, count % sca_pci_load_interval);
}