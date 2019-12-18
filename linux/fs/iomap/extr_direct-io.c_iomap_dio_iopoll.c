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
struct request_queue {int dummy; } ;
struct kiocb {int /*<<< orphan*/  ki_cookie; int /*<<< orphan*/  private; } ;

/* Variables and functions */
 struct request_queue* READ_ONCE (int /*<<< orphan*/ ) ; 
 int blk_poll (struct request_queue*,struct request_queue*,int) ; 

int iomap_dio_iopoll(struct kiocb *kiocb, bool spin)
{
	struct request_queue *q = READ_ONCE(kiocb->private);

	if (!q)
		return 0;
	return blk_poll(q, READ_ONCE(kiocb->ki_cookie), spin);
}