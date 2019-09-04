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
typedef  void const nvmem_cell ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t ETH_ALEN ; 
 scalar_t__ IS_ERR (void const*) ; 
 int PTR_ERR (void const*) ; 
 int /*<<< orphan*/  ether_addr_copy (void*,void const*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (void const*) ; 
 int /*<<< orphan*/  kfree (void const*) ; 
 int /*<<< orphan*/  nvmem_cell_put (void const*) ; 
 void* nvmem_cell_read (void const*,size_t*) ; 
 void* of_nvmem_cell_get (struct device_node*,char*) ; 

int of_get_nvmem_mac_address(struct device_node *np, void *addr)
{
	struct nvmem_cell *cell;
	const void *mac;
	size_t len;
	int ret;

	cell = of_nvmem_cell_get(np, "mac-address");
	if (IS_ERR(cell))
		return PTR_ERR(cell);

	mac = nvmem_cell_read(cell, &len);

	nvmem_cell_put(cell);

	if (IS_ERR(mac))
		return PTR_ERR(mac);

	if (len < ETH_ALEN || !is_valid_ether_addr(mac)) {
		ret = -EINVAL;
	} else {
		ether_addr_copy(addr, mac);
		ret = 0;
	}

	kfree(mac);

	return ret;
}