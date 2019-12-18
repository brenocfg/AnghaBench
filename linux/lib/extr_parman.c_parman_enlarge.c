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
struct parman {unsigned long limit_count; int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {unsigned long resize_step; int (* resize ) (int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int parman_enlarge(struct parman *parman)
{
	unsigned long new_count = parman->limit_count +
				  parman->ops->resize_step;
	int err;

	err = parman->ops->resize(parman->priv, new_count);
	if (err)
		return err;
	parman->limit_count = new_count;
	return 0;
}