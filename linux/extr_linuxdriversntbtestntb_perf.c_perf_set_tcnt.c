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
typedef  scalar_t__ u8 ;
struct perf_ctx {int /*<<< orphan*/  busy_flag; scalar_t__ tcnt; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MAX_THREADS_CNT ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_set_tcnt(struct perf_ctx *perf, u8 tcnt)
{
	if (tcnt == 0 || tcnt > MAX_THREADS_CNT)
		return -EINVAL;

	if (test_and_set_bit_lock(0, &perf->busy_flag))
		return -EBUSY;

	perf->tcnt = tcnt;

	clear_bit_unlock(0, &perf->busy_flag);

	return 0;
}