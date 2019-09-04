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
struct nfs_cache_defer_req {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs_cache_defer_req*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void nfs_cache_defer_req_put(struct nfs_cache_defer_req *dreq)
{
	if (refcount_dec_and_test(&dreq->count))
		kfree(dreq);
}