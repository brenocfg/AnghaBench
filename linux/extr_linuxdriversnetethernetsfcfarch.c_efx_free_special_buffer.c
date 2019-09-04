#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  len; scalar_t__ dma_addr; } ;
struct efx_special_buffer {scalar_t__ entries; TYPE_1__ buf; scalar_t__ index; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,TYPE_1__*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
efx_free_special_buffer(struct efx_nic *efx, struct efx_special_buffer *buffer)
{
	if (!buffer->buf.addr)
		return;

	netif_dbg(efx, hw, efx->net_dev,
		  "deallocating special buffers %d-%d at %llx+%x "
		  "(virt %p phys %llx)\n", buffer->index,
		  buffer->index + buffer->entries - 1,
		  (u64)buffer->buf.dma_addr, buffer->buf.len,
		  buffer->buf.addr, (u64)virt_to_phys(buffer->buf.addr));

	efx_nic_free_buffer(efx, &buffer->buf);
	buffer->entries = 0;
}