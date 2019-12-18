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
struct key {int /*<<< orphan*/  sem; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_FLAG_INVALIDATED ; 
 int /*<<< orphan*/  down_write_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 int /*<<< orphan*/  key_schedule_gc_links () ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void key_invalidate(struct key *key)
{
	kenter("%d", key_serial(key));

	key_check(key);

	if (!test_bit(KEY_FLAG_INVALIDATED, &key->flags)) {
		down_write_nested(&key->sem, 1);
		if (!test_and_set_bit(KEY_FLAG_INVALIDATED, &key->flags))
			key_schedule_gc_links();
		up_write(&key->sem);
	}
}