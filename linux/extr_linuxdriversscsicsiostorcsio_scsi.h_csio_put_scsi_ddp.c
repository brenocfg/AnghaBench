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
struct csio_scsim {int /*<<< orphan*/  ddp_freelist; } ;
struct csio_dma_buf {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_scsim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_free_ddp ; 

__attribute__((used)) static inline void
csio_put_scsi_ddp(struct csio_scsim *scm, struct csio_dma_buf *ddp)
{
	list_add_tail(&ddp->list, &scm->ddp_freelist);
	CSIO_INC_STATS(scm, n_free_ddp);
}