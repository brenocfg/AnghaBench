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
struct nfsd4_copy {int stopped; TYPE_1__* cp_clp; } ;
struct TYPE_2__ {int /*<<< orphan*/  async_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
check_and_set_stop_copy(struct nfsd4_copy *copy)
{
	bool value;

	spin_lock(&copy->cp_clp->async_lock);
	value = copy->stopped;
	if (!copy->stopped)
		copy->stopped = true;
	spin_unlock(&copy->cp_clp->async_lock);
	return value;
}