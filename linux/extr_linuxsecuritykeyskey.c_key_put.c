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
struct key {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  key_check (struct key*) ; 
 int /*<<< orphan*/  key_gc_work ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void key_put(struct key *key)
{
	if (key) {
		key_check(key);

		if (refcount_dec_and_test(&key->usage))
			schedule_work(&key_gc_work);
	}
}