#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int logical_address; int /*<<< orphan*/  Device; int /*<<< orphan*/  Desc; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pDevice; int /*<<< orphan*/ * pDataFlashDesc; } ;
typedef  TYPE_1__* AT91PS_DataFlash ;

/* Variables and functions */
 int CFG_MAX_DATAFLASH_BANKS ; 
 TYPE_2__* dataflash_info ; 

__attribute__((used)) static AT91PS_DataFlash AT91F_DataflashSelect(AT91PS_DataFlash pFlash,
                                              unsigned int *addr)
{
	char addr_valid = 0;
	int i;

	for (i = 0; i < CFG_MAX_DATAFLASH_BANKS; i++)
		if ((*addr & 0xFF000000) == dataflash_info[i].logical_address) {
			addr_valid = 1;
			break;
		}
	if (!addr_valid) {
		pFlash = (AT91PS_DataFlash) 0;
		return pFlash;
	}
	pFlash->pDataFlashDesc = &(dataflash_info[i].Desc);
	pFlash->pDevice = &(dataflash_info[i].Device);
	*addr -= dataflash_info[i].logical_address;
	return (pFlash);
}