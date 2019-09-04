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
struct cb_data {int (* fn_known_sch ) (struct subchannel*,void*) ;int (* fn_unknown_sch ) (struct subchannel_id,void*) ;int /*<<< orphan*/ * set; void* data; } ;

/* Variables and functions */
 int bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_fn_all_sch ; 
 int /*<<< orphan*/  call_fn_known_sch ; 
 int /*<<< orphan*/  call_fn_unknown_sch ; 
 int /*<<< orphan*/  css_bus_type ; 
 int for_each_subchannel (int /*<<< orphan*/ ,struct cb_data*) ; 
 int /*<<< orphan*/  idset_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idset_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * idset_sch_new () ; 

int for_each_subchannel_staged(int (*fn_known)(struct subchannel *, void *),
			       int (*fn_unknown)(struct subchannel_id,
			       void *), void *data)
{
	struct cb_data cb;
	int rc;

	cb.data = data;
	cb.fn_known_sch = fn_known;
	cb.fn_unknown_sch = fn_unknown;

	if (fn_known && !fn_unknown) {
		/* Skip idset allocation in case of known-only loop. */
		cb.set = NULL;
		return bus_for_each_dev(&css_bus_type, NULL, &cb,
					call_fn_known_sch);
	}

	cb.set = idset_sch_new();
	if (!cb.set)
		/* fall back to brute force scanning in case of oom */
		return for_each_subchannel(call_fn_all_sch, &cb);

	idset_fill(cb.set);

	/* Process registered subchannels. */
	rc = bus_for_each_dev(&css_bus_type, NULL, &cb, call_fn_known_sch);
	if (rc)
		goto out;
	/* Process unregistered subchannels. */
	if (fn_unknown)
		rc = for_each_subchannel(call_fn_unknown_sch, &cb);
out:
	idset_free(cb.set);

	return rc;
}