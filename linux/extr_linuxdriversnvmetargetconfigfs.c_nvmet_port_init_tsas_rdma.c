#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cms; int /*<<< orphan*/  prtype; int /*<<< orphan*/  qptype; } ;
struct TYPE_5__ {TYPE_1__ rdma; } ;
struct TYPE_6__ {TYPE_2__ tsas; } ;
struct nvmet_port {TYPE_3__ disc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMF_RDMA_CMS_RDMA_CM ; 
 int /*<<< orphan*/  NVMF_RDMA_PRTYPE_NOT_SPECIFIED ; 
 int /*<<< orphan*/  NVMF_RDMA_QPTYPE_CONNECTED ; 

__attribute__((used)) static void nvmet_port_init_tsas_rdma(struct nvmet_port *port)
{
	port->disc_addr.tsas.rdma.qptype = NVMF_RDMA_QPTYPE_CONNECTED;
	port->disc_addr.tsas.rdma.prtype = NVMF_RDMA_PRTYPE_NOT_SPECIFIED;
	port->disc_addr.tsas.rdma.cms = NVMF_RDMA_CMS_RDMA_CM;
}