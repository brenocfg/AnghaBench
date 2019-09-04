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
struct slot_map {scalar_t__ c; TYPE_1__ q; int /*<<< orphan*/  map; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int wait_for_free (struct slot_map*) ; 

__attribute__((used)) static int get(struct slot_map *m)
{
	int res = 0;
	spin_lock(&m->q.lock);
	if (unlikely(m->c <= 0))
		res = wait_for_free(m);
	if (likely(!res)) {
		m->c--;
		res = find_first_zero_bit(m->map, m->count);
		__set_bit(res, m->map);
	}
	spin_unlock(&m->q.lock);
	return res;
}