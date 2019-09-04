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
struct xfs_log_vec {struct xfs_log_vec* lv_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (struct xfs_log_vec*) ; 

__attribute__((used)) static void
xlog_cil_free_logvec(
	struct xfs_log_vec	*log_vector)
{
	struct xfs_log_vec	*lv;

	for (lv = log_vector; lv; ) {
		struct xfs_log_vec *next = lv->lv_next;
		kmem_free(lv);
		lv = next;
	}
}