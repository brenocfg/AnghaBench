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
struct csio_scsim {int /*<<< orphan*/  ioreq_freelist; } ;
struct TYPE_2__ {int /*<<< orphan*/  sm_list; } ;
struct csio_ioreq {TYPE_1__ sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_scsim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_free_ioreq ; 

__attribute__((used)) static inline void
csio_put_scsi_ioreq(struct csio_scsim *scm, struct csio_ioreq *ioreq)
{
	list_add_tail(&ioreq->sm.sm_list, &scm->ioreq_freelist);
	CSIO_INC_STATS(scm, n_free_ioreq);
}