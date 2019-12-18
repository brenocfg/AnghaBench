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
typedef  unsigned int time64_t ;
struct key {unsigned int expiry; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 unsigned int key_gc_delay ; 
 int /*<<< orphan*/  key_schedule_gc (unsigned int) ; 
 unsigned int ktime_get_real_seconds () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void key_set_timeout(struct key *key, unsigned timeout)
{
	time64_t expiry = 0;

	/* make the changes with the locks held to prevent races */
	down_write(&key->sem);

	if (timeout > 0)
		expiry = ktime_get_real_seconds() + timeout;

	key->expiry = expiry;
	key_schedule_gc(key->expiry + key_gc_delay);

	up_write(&key->sem);
}