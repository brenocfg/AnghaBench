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
struct p9_fcall {int /*<<< orphan*/  sdata; scalar_t__ cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void p9_fcall_fini(struct p9_fcall *fc)
{
	/* sdata can be NULL for interrupted requests in trans_rdma,
	 * and kmem_cache_free does not do NULL-check for us
	 */
	if (unlikely(!fc->sdata))
		return;

	if (fc->cache)
		kmem_cache_free(fc->cache, fc->sdata);
	else
		kfree(fc->sdata);
}