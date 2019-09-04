#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * epthru; int /*<<< orphan*/  epthru_dma_addr; int /*<<< orphan*/ * pthru; int /*<<< orphan*/  pthru_dma_addr; int /*<<< orphan*/ * sgl64; int /*<<< orphan*/  sgl_dma_addr; } ;
typedef  TYPE_1__ scb_t ;
typedef  int /*<<< orphan*/  mega_sgl64 ;
typedef  int /*<<< orphan*/  mega_passthru ;
typedef  int /*<<< orphan*/  mega_ext_passthru ;
struct TYPE_5__ {int max_cmds; int sglen; int /*<<< orphan*/  dev; TYPE_1__* scb_list; } ;
typedef  TYPE_2__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mega_free_sgl(adapter_t *adapter)
{
	scb_t	*scb;
	int	i;

	for(i = 0; i < adapter->max_cmds; i++) {

		scb = &adapter->scb_list[i];

		if( scb->sgl64 ) {
			pci_free_consistent(adapter->dev,
				sizeof(mega_sgl64) * adapter->sglen,
				scb->sgl64,
				scb->sgl_dma_addr);

			scb->sgl64 = NULL;
		}

		if( scb->pthru ) {
			pci_free_consistent(adapter->dev, sizeof(mega_passthru),
				scb->pthru, scb->pthru_dma_addr);

			scb->pthru = NULL;
		}

		if( scb->epthru ) {
			pci_free_consistent(adapter->dev,
				sizeof(mega_ext_passthru),
				scb->epthru, scb->epthru_dma_addr);

			scb->epthru = NULL;
		}

	}
}