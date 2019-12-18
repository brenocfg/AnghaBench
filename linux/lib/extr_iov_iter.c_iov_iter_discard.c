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
struct iov_iter {unsigned int type; size_t count; scalar_t__ iov_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int ITER_DISCARD ; 
 unsigned int READ ; 

void iov_iter_discard(struct iov_iter *i, unsigned int direction, size_t count)
{
	BUG_ON(direction != READ);
	i->type = ITER_DISCARD | READ;
	i->count = count;
	i->iov_offset = 0;
}