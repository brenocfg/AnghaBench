#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ refcount_t ;

/* Variables and functions */
 int atomic_try_cmpxchg_release (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

bool refcount_dec_if_one(refcount_t *r)
{
	int val = 1;

	return atomic_try_cmpxchg_release(&r->refs, &val, 0);
}