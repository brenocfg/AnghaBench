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
struct aa_task_ctx {int /*<<< orphan*/  onexec; int /*<<< orphan*/  previous; int /*<<< orphan*/  nnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_get_label (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aa_dup_task_ctx(struct aa_task_ctx *new,
				   const struct aa_task_ctx *old)
{
	*new = *old;
	aa_get_label(new->nnp);
	aa_get_label(new->previous);
	aa_get_label(new->onexec);
}