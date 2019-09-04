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
typedef  scalar_t__ u64 ;
struct seq_file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct dlm_lkb {int lkb_flags; int /*<<< orphan*/  lkb_last_bast_time; int /*<<< orphan*/  lkb_timestamp; int /*<<< orphan*/  lkb_lvbseq; int /*<<< orphan*/  lkb_wait_type; TYPE_2__ lkb_last_bast; int /*<<< orphan*/  lkb_rqmode; int /*<<< orphan*/  lkb_grmode; int /*<<< orphan*/  lkb_status; int /*<<< orphan*/  lkb_exflags; int /*<<< orphan*/  lkb_ownpid; int /*<<< orphan*/  lkb_remid; int /*<<< orphan*/  lkb_nodeid; int /*<<< orphan*/  lkb_id; TYPE_1__* lkb_ua; } ;
struct TYPE_3__ {scalar_t__ xid; } ;

/* Variables and functions */
 int DLM_IFL_USER ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 

__attribute__((used)) static void print_format3_lock(struct seq_file *s, struct dlm_lkb *lkb,
			      int rsb_lookup)
{
	u64 xid = 0;

	if (lkb->lkb_flags & DLM_IFL_USER) {
		if (lkb->lkb_ua)
			xid = lkb->lkb_ua->xid;
	}

	seq_printf(s, "lkb %x %d %x %u %llu %x %x %d %d %d %d %d %d %u %llu %llu\n",
		   lkb->lkb_id,
		   lkb->lkb_nodeid,
		   lkb->lkb_remid,
		   lkb->lkb_ownpid,
		   (unsigned long long)xid,
		   lkb->lkb_exflags,
		   lkb->lkb_flags,
		   lkb->lkb_status,
		   lkb->lkb_grmode,
		   lkb->lkb_rqmode,
		   lkb->lkb_last_bast.mode,
		   rsb_lookup,
		   lkb->lkb_wait_type,
		   lkb->lkb_lvbseq,
		   (unsigned long long)ktime_to_ns(lkb->lkb_timestamp),
		   (unsigned long long)ktime_to_ns(lkb->lkb_last_bast_time));
}