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
struct qm_mr {int fill; int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  mr_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qm_mr_next(struct qm_portal *portal)
{
	struct qm_mr *mr = &portal->mr;

	DPAA_ASSERT(mr->fill);
	mr->cursor = mr_inc(mr->cursor);
	return --mr->fill;
}