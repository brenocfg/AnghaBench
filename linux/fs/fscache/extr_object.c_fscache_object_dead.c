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
struct fscache_state {int dummy; } ;
struct fscache_object {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE_OBJECT_RUN_AFTER_DEAD ; 
 struct fscache_state const* NO_TRANSIT ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const struct fscache_state *fscache_object_dead(struct fscache_object *object,
						       int event)
{
	if (!test_and_set_bit(FSCACHE_OBJECT_RUN_AFTER_DEAD,
			      &object->flags))
		return NO_TRANSIT;

	WARN(true, "FS-Cache object redispatched after death");
	return NO_TRANSIT;
}