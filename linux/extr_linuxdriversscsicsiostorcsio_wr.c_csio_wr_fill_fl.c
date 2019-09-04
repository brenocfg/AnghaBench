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
typedef  int uint64_t ;
struct csio_sge {int /*<<< orphan*/ * sge_fl_buf_size; } ;
struct csio_wrm {struct csio_sge sge; } ;
struct TYPE_3__ {int sreg; struct csio_dma_buf* bufs; } ;
struct TYPE_4__ {TYPE_1__ fl; } ;
struct csio_q {int credits; TYPE_2__ un; scalar_t__ vstart; } ;
struct csio_hw {int /*<<< orphan*/  pdev; } ;
struct csio_dma_buf {int paddr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,int) ; 
 struct csio_wrm* csio_hw_to_wrm (struct csio_hw*) ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
csio_wr_fill_fl(struct csio_hw *hw, struct csio_q *flq)
{
	struct csio_wrm *wrm = csio_hw_to_wrm(hw);
	struct csio_sge *sge = &wrm->sge;
	__be64 *d = (__be64 *)(flq->vstart);
	struct csio_dma_buf *buf = &flq->un.fl.bufs[0];
	uint64_t paddr;
	int sreg = flq->un.fl.sreg;
	int n = flq->credits;

	while (n--) {
		buf->len = sge->sge_fl_buf_size[sreg];
		buf->vaddr = pci_alloc_consistent(hw->pdev, buf->len,
						  &buf->paddr);
		if (!buf->vaddr) {
			csio_err(hw, "Could only fill %d buffers!\n", n + 1);
			return -ENOMEM;
		}

		paddr = buf->paddr | (sreg & 0xF);

		*d++ = cpu_to_be64(paddr);
		buf++;
	}

	return 0;
}