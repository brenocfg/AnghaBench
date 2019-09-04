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
struct netdev_phys_item_id {int /*<<< orphan*/  id_len; int /*<<< orphan*/  id; } ;
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ef10_get_phys_port_id(struct efx_nic *efx,
				     struct netdev_phys_item_id *ppid)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	if (!is_valid_ether_addr(nic_data->port_id))
		return -EOPNOTSUPP;

	ppid->id_len = ETH_ALEN;
	memcpy(ppid->id, nic_data->port_id, ppid->id_len);

	return 0;
}