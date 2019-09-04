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
struct bfa_tskim_s {int dummy; } ;
struct bfa_ioim_s {TYPE_1__* iosp; int /*<<< orphan*/  itnim; int /*<<< orphan*/  iotag; int /*<<< orphan*/  bfa; } ;
struct TYPE_2__ {struct bfa_tskim_s* tskim; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOIM_SM_CLEANUP ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_tmaborts ; 

void
bfa_ioim_cleanup_tm(struct bfa_ioim_s *ioim, struct bfa_tskim_s *tskim)
{
	bfa_trc(ioim->bfa, ioim->iotag);
	bfa_stats(ioim->itnim, io_tmaborts);

	ioim->iosp->tskim = tskim;
	bfa_sm_send_event(ioim, BFA_IOIM_SM_CLEANUP);
}