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
typedef  scalar_t__ u32 ;
struct bfi_flash_read_req_s {int /*<<< orphan*/  alen; int /*<<< orphan*/  mh; void* length; void* offset; int /*<<< orphan*/  instance; void* type; } ;
struct TYPE_2__ {scalar_t__ msg; } ;
struct bfa_flash_s {scalar_t__ residue; TYPE_1__ mb; int /*<<< orphan*/  ioc; int /*<<< orphan*/  dbuf_pa; scalar_t__ offset; scalar_t__ addr_off; int /*<<< orphan*/  instance; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ BFA_FLASH_DMA_BUF_SZ ; 
 int /*<<< orphan*/  BFI_FLASH_H2I_READ_REQ ; 
 int /*<<< orphan*/  BFI_MC_FLASH ; 
 void* be32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  bfa_alen_set (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_flash_read_send(void *cbarg)
{
	struct bfa_flash_s *flash = cbarg;
	struct bfi_flash_read_req_s *msg =
			(struct bfi_flash_read_req_s *) flash->mb.msg;
	u32	len;

	msg->type = be32_to_cpu(flash->type);
	msg->instance = flash->instance;
	msg->offset = be32_to_cpu(flash->addr_off + flash->offset);
	len = (flash->residue < BFA_FLASH_DMA_BUF_SZ) ?
			flash->residue : BFA_FLASH_DMA_BUF_SZ;
	msg->length = be32_to_cpu(len);
	bfi_h2i_set(msg->mh, BFI_MC_FLASH, BFI_FLASH_H2I_READ_REQ,
		bfa_ioc_portid(flash->ioc));
	bfa_alen_set(&msg->alen, len, flash->dbuf_pa);
	bfa_ioc_mbox_queue(flash->ioc, &flash->mb);
}