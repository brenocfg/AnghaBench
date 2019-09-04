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
struct csio_mbm {int /*<<< orphan*/  cbfn_q; int /*<<< orphan*/  req_q; int /*<<< orphan*/ * mcurrent; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void
csio_mbm_exit(struct csio_mbm *mbm)
{
	del_timer_sync(&mbm->timer);

	CSIO_DB_ASSERT(mbm->mcurrent == NULL);
	CSIO_DB_ASSERT(list_empty(&mbm->req_q));
	CSIO_DB_ASSERT(list_empty(&mbm->cbfn_q));
}