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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct slot_map {int c; TYPE_1__ q; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_all_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up_locked (TYPE_1__*) ; 

__attribute__((used)) static void put(struct slot_map *m, int slot)
{
	int v;
	spin_lock(&m->q.lock);
	__clear_bit(slot, m->map);
	v = ++m->c;
	if (v > 0)
		wake_up_locked(&m->q);
	if (unlikely(v == -1))     /* finished dying */
		wake_up_all_locked(&m->q);
	spin_unlock(&m->q.lock);
}