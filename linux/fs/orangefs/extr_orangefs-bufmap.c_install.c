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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct slot_map {int c; int count; unsigned long* map; TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all_locked (TYPE_1__*) ; 

__attribute__((used)) static void install(struct slot_map *m, int count, unsigned long *map)
{
	spin_lock(&m->q.lock);
	m->c = m->count = count;
	m->map = map;
	wake_up_all_locked(&m->q);
	spin_unlock(&m->q.lock);
}