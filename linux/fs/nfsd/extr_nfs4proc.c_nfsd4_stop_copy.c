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
struct nfsd4_copy {int /*<<< orphan*/  copy_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_and_set_stop_copy (struct nfsd4_copy*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_put_copy (struct nfsd4_copy*) ; 

__attribute__((used)) static void nfsd4_stop_copy(struct nfsd4_copy *copy)
{
	/* only 1 thread should stop the copy */
	if (!check_and_set_stop_copy(copy))
		kthread_stop(copy->copy_task);
	nfs4_put_copy(copy);
}