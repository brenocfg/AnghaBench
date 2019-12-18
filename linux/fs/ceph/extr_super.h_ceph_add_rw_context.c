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
struct ceph_rw_context {int /*<<< orphan*/  list; } ;
struct ceph_file_info {int /*<<< orphan*/  rw_contexts_lock; int /*<<< orphan*/  rw_contexts; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ceph_add_rw_context(struct ceph_file_info *cf,
				       struct ceph_rw_context *ctx)
{
	spin_lock(&cf->rw_contexts_lock);
	list_add(&ctx->list, &cf->rw_contexts);
	spin_unlock(&cf->rw_contexts_lock);
}