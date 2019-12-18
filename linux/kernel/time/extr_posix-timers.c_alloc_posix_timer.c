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
struct k_itimer {TYPE_1__* sigq; } ;
struct TYPE_2__ {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clear_siginfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct k_itimer*) ; 
 struct k_itimer* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_timers_cache ; 
 TYPE_1__* sigqueue_alloc () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct k_itimer * alloc_posix_timer(void)
{
	struct k_itimer *tmr;
	tmr = kmem_cache_zalloc(posix_timers_cache, GFP_KERNEL);
	if (!tmr)
		return tmr;
	if (unlikely(!(tmr->sigq = sigqueue_alloc()))) {
		kmem_cache_free(posix_timers_cache, tmr);
		return NULL;
	}
	clear_siginfo(&tmr->sigq->info);
	return tmr;
}