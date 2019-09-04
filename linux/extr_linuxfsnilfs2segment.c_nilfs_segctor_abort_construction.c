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
struct the_nilfs {int /*<<< orphan*/  ns_sufile; } ;
struct TYPE_2__ {int flags; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_nfreesegs; int /*<<< orphan*/  sc_freesegs; TYPE_1__ sc_stage; int /*<<< orphan*/  sc_segbufs; int /*<<< orphan*/  sc_write_logs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int NILFS_CF_SUFREED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logs ; 
 int /*<<< orphan*/  nilfs_abort_logs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nilfs_cancel_segusage (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_destroy_logs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_free_incomplete_logs (int /*<<< orphan*/ *,struct the_nilfs*) ; 
 int nilfs_sufile_cancel_freev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nilfs_wait_on_logs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_segctor_abort_construction(struct nilfs_sc_info *sci,
					     struct the_nilfs *nilfs, int err)
{
	LIST_HEAD(logs);
	int ret;

	list_splice_tail_init(&sci->sc_write_logs, &logs);
	ret = nilfs_wait_on_logs(&logs);
	nilfs_abort_logs(&logs, ret ? : err);

	list_splice_tail_init(&sci->sc_segbufs, &logs);
	nilfs_cancel_segusage(&logs, nilfs->ns_sufile);
	nilfs_free_incomplete_logs(&logs, nilfs);

	if (sci->sc_stage.flags & NILFS_CF_SUFREED) {
		ret = nilfs_sufile_cancel_freev(nilfs->ns_sufile,
						sci->sc_freesegs,
						sci->sc_nfreesegs,
						NULL);
		WARN_ON(ret); /* do not happen */
	}

	nilfs_destroy_logs(&logs);
}