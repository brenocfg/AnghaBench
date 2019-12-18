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
struct TYPE_2__ {int failed; struct mp_filter* parent; scalar_t__ error_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pending (scalar_t__) ; 

void mp_filter_internal_mark_failed(struct mp_filter *f)
{
    while (f) {
        f->in->failed = true;
        if (f->in->error_handler) {
            add_pending(f->in->error_handler);
            break;
        }
        f = f->in->parent;
    }
}