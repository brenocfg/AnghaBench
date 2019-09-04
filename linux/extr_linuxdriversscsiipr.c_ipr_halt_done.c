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
struct ipr_cmnd {TYPE_1__* hrrq; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  hrrq_free_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipr_halt_done(struct ipr_cmnd *ipr_cmd)
{
	list_add_tail(&ipr_cmd->queue, &ipr_cmd->hrrq->hrrq_free_q);
}