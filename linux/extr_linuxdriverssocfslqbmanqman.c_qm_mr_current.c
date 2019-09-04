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
typedef  union qm_mr_entry {int dummy; } qm_mr_entry ;
struct qm_mr {union qm_mr_entry const* cursor; int /*<<< orphan*/  fill; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */

__attribute__((used)) static inline const union qm_mr_entry *qm_mr_current(struct qm_portal *portal)
{
	struct qm_mr *mr = &portal->mr;

	if (!mr->fill)
		return NULL;
	return mr->cursor;
}