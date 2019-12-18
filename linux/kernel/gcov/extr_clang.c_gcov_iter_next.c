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
struct gcov_iterator {scalar_t__ pos; scalar_t__ size; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ITER_STRIDE ; 

int gcov_iter_next(struct gcov_iterator *iter)
{
	if (iter->pos < iter->size)
		iter->pos += ITER_STRIDE;

	if (iter->pos >= iter->size)
		return -EINVAL;

	return 0;
}