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
struct umh_info {scalar_t__ pid; int /*<<< orphan*/  pipe_from_umh; int /*<<< orphan*/  pipe_to_umh; } ;
struct TYPE_2__ {int stop; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_1__ bpfilter_ops ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bpfilter_umh_cleanup(struct umh_info *info)
{
	mutex_lock(&bpfilter_ops.lock);
	bpfilter_ops.stop = true;
	fput(info->pipe_to_umh);
	fput(info->pipe_from_umh);
	info->pid = 0;
	mutex_unlock(&bpfilter_ops.lock);
}