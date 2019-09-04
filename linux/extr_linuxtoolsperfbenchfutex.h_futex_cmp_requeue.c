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
typedef  int /*<<< orphan*/  u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUTEX_CMP_REQUEUE ; 
 int futex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
futex_cmp_requeue(u_int32_t *uaddr, u_int32_t val, u_int32_t *uaddr2, int nr_wake,
		 int nr_requeue, int opflags)
{
	return futex(uaddr, FUTEX_CMP_REQUEUE, nr_wake, nr_requeue, uaddr2,
		 val, opflags);
}