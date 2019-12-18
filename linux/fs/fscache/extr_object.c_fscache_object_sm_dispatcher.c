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
struct fscache_transition {int events; struct fscache_state const* transit_to; } ;
typedef  struct fscache_state {struct fscache_transition* transitions; struct fscache_state const* (* work ) (struct fscache_object*,int) ;int /*<<< orphan*/  name; } const fscache_state ;
struct fscache_object {unsigned long events; unsigned long event_mask; unsigned long oob_event_mask; struct fscache_state const* state; int /*<<< orphan*/  debug_id; struct fscache_transition* oob_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG () ; 
 struct fscache_state const* NO_TRANSIT ; 
 int /*<<< orphan*/  OBJECT_DEAD ; 
 struct fscache_state const* STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ,unsigned long,...) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int fls (unsigned long) ; 
 int /*<<< orphan*/  fscache_enqueue_object (struct fscache_object*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 struct fscache_state const* stub1 (struct fscache_object*,int) ; 
 int /*<<< orphan*/  trace_fscache_osm (struct fscache_object*,struct fscache_state const*,int,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void fscache_object_sm_dispatcher(struct fscache_object *object)
{
	const struct fscache_transition *t;
	const struct fscache_state *state, *new_state;
	unsigned long events, event_mask;
	bool oob;
	int event = -1;

	ASSERT(object != NULL);

	_enter("{OBJ%x,%s,%lx}",
	       object->debug_id, object->state->name, object->events);

	event_mask = object->event_mask;
restart:
	object->event_mask = 0; /* Mask normal event handling */
	state = object->state;
restart_masked:
	events = object->events;

	/* Handle any out-of-band events (typically an error) */
	if (events & object->oob_event_mask) {
		_debug("{OBJ%x} oob %lx",
		       object->debug_id, events & object->oob_event_mask);
		oob = true;
		for (t = object->oob_table; t->events; t++) {
			if (events & t->events) {
				state = t->transit_to;
				ASSERT(state->work != NULL);
				event = fls(events & t->events) - 1;
				__clear_bit(event, &object->oob_event_mask);
				clear_bit(event, &object->events);
				goto execute_work_state;
			}
		}
	}
	oob = false;

	/* Wait states are just transition tables */
	if (!state->work) {
		if (events & event_mask) {
			for (t = state->transitions; t->events; t++) {
				if (events & t->events) {
					new_state = t->transit_to;
					event = fls(events & t->events) - 1;
					trace_fscache_osm(object, state,
							  true, false, event);
					clear_bit(event, &object->events);
					_debug("{OBJ%x} ev %d: %s -> %s",
					       object->debug_id, event,
					       state->name, new_state->name);
					object->state = state = new_state;
					goto execute_work_state;
				}
			}

			/* The event mask didn't include all the tabled bits */
			BUG();
		}
		/* Randomly woke up */
		goto unmask_events;
	}

execute_work_state:
	_debug("{OBJ%x} exec %s", object->debug_id, state->name);

	trace_fscache_osm(object, state, false, oob, event);
	new_state = state->work(object, event);
	event = -1;
	if (new_state == NO_TRANSIT) {
		_debug("{OBJ%x} %s notrans", object->debug_id, state->name);
		if (unlikely(state == STATE(OBJECT_DEAD))) {
			_leave(" [dead]");
			return;
		}
		fscache_enqueue_object(object);
		event_mask = object->oob_event_mask;
		goto unmask_events;
	}

	_debug("{OBJ%x} %s -> %s",
	       object->debug_id, state->name, new_state->name);
	object->state = state = new_state;

	if (state->work) {
		if (unlikely(state == STATE(OBJECT_DEAD))) {
			_leave(" [dead]");
			return;
		}
		goto restart_masked;
	}

	/* Transited to wait state */
	event_mask = object->oob_event_mask;
	for (t = state->transitions; t->events; t++)
		event_mask |= t->events;

unmask_events:
	object->event_mask = event_mask;
	smp_mb();
	events = object->events;
	if (events & event_mask)
		goto restart;
	_leave(" [msk %lx]", event_mask);
}