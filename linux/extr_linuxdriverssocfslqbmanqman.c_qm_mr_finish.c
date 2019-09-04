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
struct qm_mr {scalar_t__ ci; int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 scalar_t__ mr_ptr2idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static inline void qm_mr_finish(struct qm_portal *portal)
{
	struct qm_mr *mr = &portal->mr;

	if (mr->ci != mr_ptr2idx(mr->cursor))
		pr_crit("Ignoring completed MR entries\n");
}