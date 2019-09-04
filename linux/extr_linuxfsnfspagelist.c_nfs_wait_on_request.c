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
struct nfs_page {int /*<<< orphan*/  wb_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_BUSY ; 
 int /*<<< orphan*/  PG_CONTENDED2 ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_on_bit_io (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nfs_wait_on_request(struct nfs_page *req)
{
	if (!test_bit(PG_BUSY, &req->wb_flags))
		return 0;
	set_bit(PG_CONTENDED2, &req->wb_flags);
	smp_mb__after_atomic();
	return wait_on_bit_io(&req->wb_flags, PG_BUSY,
			      TASK_UNINTERRUPTIBLE);
}