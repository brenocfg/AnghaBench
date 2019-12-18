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
struct intel_pt_queue {TYPE_1__* last_branch_rb; scalar_t__ last_branch_pos; } ;
struct TYPE_2__ {scalar_t__ nr; } ;

/* Variables and functions */

__attribute__((used)) static inline void intel_pt_reset_last_branch_rb(struct intel_pt_queue *ptq)
{
	ptq->last_branch_pos = 0;
	ptq->last_branch_rb->nr = 0;
}