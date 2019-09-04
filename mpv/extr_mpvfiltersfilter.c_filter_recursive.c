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
struct filter_runner {int /*<<< orphan*/  root_filter; int /*<<< orphan*/  external_pending; scalar_t__ filtering; } ;
struct TYPE_2__ {struct filter_runner* runner; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct mp_filter*) ; 
 int /*<<< orphan*/  mp_filter_run (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter_recursive(struct mp_filter *f)
{
    assert(f);
    struct filter_runner *r = f->in->runner;

    // Never do internal filtering recursively.
    if (r->filtering)
        return;

    // Also don't lose the pending state, which the user may or may not
    // care about.
    r->external_pending |= mp_filter_run(r->root_filter);
}