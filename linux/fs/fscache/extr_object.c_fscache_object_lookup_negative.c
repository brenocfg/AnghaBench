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
struct fscache_object {int /*<<< orphan*/  flags; TYPE_1__* state; int /*<<< orphan*/  debug_id; struct fscache_cookie* cookie; } ;
struct fscache_cookie {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE_COOKIE_LOOKING_UP ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_NO_DATA_YET ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_UNAVAILABLE ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_IS_LOOKED_UP ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_n_object_lookups_negative ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void fscache_object_lookup_negative(struct fscache_object *object)
{
	struct fscache_cookie *cookie = object->cookie;

	_enter("{OBJ%x,%s}", object->debug_id, object->state->name);

	if (!test_and_set_bit(FSCACHE_OBJECT_IS_LOOKED_UP, &object->flags)) {
		fscache_stat(&fscache_n_object_lookups_negative);

		/* Allow write requests to begin stacking up and read requests to begin
		 * returning ENODATA.
		 */
		set_bit(FSCACHE_COOKIE_NO_DATA_YET, &cookie->flags);
		clear_bit(FSCACHE_COOKIE_UNAVAILABLE, &cookie->flags);

		_debug("wake up lookup %p", &cookie->flags);
		clear_bit_unlock(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags);
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP);
	}
	_leave("");
}