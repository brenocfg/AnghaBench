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
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {int stop; TYPE_1__ info; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ __bpfilter_process_sockopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ bpfilter_ops ; 
 int /*<<< orphan*/  bpfilter_umh_end ; 
 int /*<<< orphan*/  bpfilter_umh_start ; 
 int fork_usermode_blob (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_umh () ; 

__attribute__((used)) static int start_umh(void)
{
	int err;

	/* fork usermode process */
	err = fork_usermode_blob(&bpfilter_umh_start,
				 &bpfilter_umh_end - &bpfilter_umh_start,
				 &bpfilter_ops.info);
	if (err)
		return err;
	bpfilter_ops.stop = false;
	pr_info("Loaded bpfilter_umh pid %d\n", bpfilter_ops.info.pid);

	/* health check that usermode process started correctly */
	if (__bpfilter_process_sockopt(NULL, 0, NULL, 0, 0) != 0) {
		shutdown_umh();
		return -EFAULT;
	}

	return 0;
}