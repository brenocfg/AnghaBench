#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvmem_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  config2_bitmap; int /*<<< orphan*/  config_bitmap; int /*<<< orphan*/  spi_flash_size; int /*<<< orphan*/  nor_flash_size; int /*<<< orphan*/  model; } ;
struct TYPE_3__ {int /*<<< orphan*/ * hwaddr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 struct nvmem_device* at24_nvmem ; 
 TYPE_2__ laguna_info ; 
 TYPE_1__ laguna_net_data ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int nvmem_device_read (struct nvmem_device*,int,int,char*) ; 

__attribute__((used)) static void at24_setup(struct nvmem_device *mem_acc, void *context)
{
	char buf[16];

	at24_nvmem = mem_acc;

	/* Read MAC addresses */
	if (nvmem_device_read(at24_nvmem, 0x100, 6, buf) == 6)
		memcpy(&laguna_net_data.hwaddr[0], buf, ETH_ALEN);
	if (nvmem_device_read(at24_nvmem, 0x106, 6, buf) == 6)
		memcpy(&laguna_net_data.hwaddr[1], buf, ETH_ALEN);
	if (nvmem_device_read(at24_nvmem, 0x10C, 6, buf) == 6)
		memcpy(&laguna_net_data.hwaddr[2], buf, ETH_ALEN);
	if (nvmem_device_read(at24_nvmem, 0x112, 6, buf) == 6)
		memcpy(&laguna_net_data.hwaddr[3], buf, ETH_ALEN);

	/* Read out Model Information */
	if (nvmem_device_read(at24_nvmem, 0x130, 16, buf) == 16)
		memcpy(&laguna_info.model, buf, 16);
	if (nvmem_device_read(at24_nvmem, 0x140, 1, buf) == 1)
		memcpy(&laguna_info.nor_flash_size, buf, 1);
	if (nvmem_device_read(at24_nvmem, 0x141, 1, buf) == 1)
		memcpy(&laguna_info.spi_flash_size, buf, 1);
	if (nvmem_device_read(at24_nvmem, 0x142, 4, buf) == 4)
		memcpy(&laguna_info.config_bitmap, buf, 4);
	if (nvmem_device_read(at24_nvmem, 0x146, 4, buf) == 4)
		memcpy(&laguna_info.config2_bitmap, buf, 4);
}