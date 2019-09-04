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
struct csio_qstatus_page {int dummy; } ;
struct csio_q {scalar_t__ vwrap; } ;
struct csio_hw {int dummy; } ;
struct TYPE_2__ {struct csio_q** q_arr; } ;

/* Variables and functions */
 TYPE_1__* csio_hw_to_wrm (struct csio_hw*) ; 
 int /*<<< orphan*/  memset (struct csio_qstatus_page*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
csio_wr_cleanup_eq_stpg(struct csio_hw *hw, int qidx)
{
	struct csio_q	*q = csio_hw_to_wrm(hw)->q_arr[qidx];
	struct csio_qstatus_page *stp = (struct csio_qstatus_page *)q->vwrap;

	memset(stp, 0, sizeof(*stp));
}