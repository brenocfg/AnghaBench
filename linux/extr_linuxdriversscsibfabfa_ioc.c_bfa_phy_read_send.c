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
struct bfi_phy_read_req_s {int /*<<< orphan*/  alen; int /*<<< orphan*/  mh; void* length; void* offset; int /*<<< orphan*/  instance; } ;
struct TYPE_2__ {scalar_t__ msg; } ;
struct bfa_phy_s {scalar_t__ residue; TYPE_1__ mb; int /*<<< orphan*/  ioc; int /*<<< orphan*/  dbuf_pa; scalar_t__ offset; scalar_t__ addr_off; int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 scalar_t__ BFA_PHY_DMA_BUF_SZ ; 
 int /*<<< orphan*/  BFI_MC_PHY ; 
 int /*<<< orphan*/  BFI_PHY_H2I_READ_REQ ; 
 int /*<<< orphan*/  bfa_alen_set (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (scalar_t__) ; 

__attribute__((used)) static void
bfa_phy_read_send(void *cbarg)
{
	struct bfa_phy_s *phy = cbarg;
	struct bfi_phy_read_req_s *msg =
			(struct bfi_phy_read_req_s *) phy->mb.msg;
	u32	len;

	msg->instance = phy->instance;
	msg->offset = cpu_to_be32(phy->addr_off + phy->offset);
	len = (phy->residue < BFA_PHY_DMA_BUF_SZ) ?
			phy->residue : BFA_PHY_DMA_BUF_SZ;
	msg->length = cpu_to_be32(len);
	bfi_h2i_set(msg->mh, BFI_MC_PHY, BFI_PHY_H2I_READ_REQ,
		bfa_ioc_portid(phy->ioc));
	bfa_alen_set(&msg->alen, len, phy->dbuf_pa);
	bfa_ioc_mbox_queue(phy->ioc, &phy->mb);
}