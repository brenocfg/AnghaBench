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
struct request {int rq_flags; scalar_t__ rq_disk; } ;

/* Variables and functions */
 int RQF_IO_STAT ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 

__attribute__((used)) static inline bool blk_do_io_stat(struct request *rq)
{
	return rq->rq_disk &&
	       (rq->rq_flags & RQF_IO_STAT) &&
		!blk_rq_is_passthrough(rq);
}