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
struct csio_q {scalar_t__ cidx; scalar_t__ credits; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_qwrap ; 

__attribute__((used)) static inline void
csio_wr_inval_flq_buf(struct csio_hw *hw, struct csio_q *flq)
{
	flq->cidx++;
	if (flq->cidx == flq->credits) {
		flq->cidx = 0;
		CSIO_INC_STATS(flq, n_qwrap);
	}
}