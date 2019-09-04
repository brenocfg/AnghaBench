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
struct kvec {int dummy; } ;
struct iov_iter {int type; unsigned long nr_segs; size_t count; scalar_t__ iov_offset; struct kvec const* kvec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ITER_KVEC ; 

void iov_iter_kvec(struct iov_iter *i, int direction,
			const struct kvec *kvec, unsigned long nr_segs,
			size_t count)
{
	BUG_ON(!(direction & ITER_KVEC));
	i->type = direction;
	i->kvec = kvec;
	i->nr_segs = nr_segs;
	i->iov_offset = 0;
	i->count = count;
}