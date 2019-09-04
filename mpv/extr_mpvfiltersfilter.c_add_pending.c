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
struct mp_filter {TYPE_1__* in; } ;
struct filter_runner {int external_pending; struct mp_filter* root_filter; int /*<<< orphan*/  num_pending; int /*<<< orphan*/  pending; } ;
struct TYPE_2__ {int pending; struct filter_runner* runner; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct filter_runner*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_filter*) ; 

__attribute__((used)) static void add_pending(struct mp_filter *f)
{
    struct filter_runner *r = f->in->runner;

    if (f->in->pending)
        return;

    // This should probably really be some sort of priority queue, but for now
    // something naive and dumb does the job too.
    f->in->pending = true;
    MP_TARRAY_APPEND(r, r->pending, r->num_pending, f);

    // Need to tell user that something changed.
    if (f == r->root_filter)
        r->external_pending = true;
}