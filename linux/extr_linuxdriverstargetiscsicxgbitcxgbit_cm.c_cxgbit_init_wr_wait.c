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
struct cxgbit_wr_wait {int /*<<< orphan*/  completion; scalar_t__ ret; } ;

/* Variables and functions */
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxgbit_init_wr_wait(struct cxgbit_wr_wait *wr_waitp)
{
	wr_waitp->ret = 0;
	reinit_completion(&wr_waitp->completion);
}