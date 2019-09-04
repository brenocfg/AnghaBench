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
struct ceph_osd_linger_request {int reg_commit_error; int /*<<< orphan*/  reg_commit_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void linger_reg_commit_complete(struct ceph_osd_linger_request *lreq,
				       int result)
{
	if (!completion_done(&lreq->reg_commit_wait)) {
		lreq->reg_commit_error = (result <= 0 ? result : 0);
		complete_all(&lreq->reg_commit_wait);
	}
}