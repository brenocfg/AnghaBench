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
typedef  int /*<<< orphan*/  pthread_mutex_t ;
struct TYPE_2__ {int /*<<< orphan*/  dep_map; } ;

/* Variables and functions */
 scalar_t__ _RET_IP_ ; 
 TYPE_1__* __get_lock (int /*<<< orphan*/ *) ; 
 int ll_pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  try_init_preload () ; 

int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
	int r;

	try_init_preload();

	lock_acquire(&__get_lock(mutex)->dep_map, 0, 1, 0, 1, NULL, (unsigned long)_RET_IP_);
	r = ll_pthread_mutex_trylock(mutex);
	if (r)
		lock_release(&__get_lock(mutex)->dep_map, 0, (unsigned long)_RET_IP_);

	return r;
}