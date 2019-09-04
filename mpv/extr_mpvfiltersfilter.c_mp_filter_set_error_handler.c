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
struct TYPE_2__ {struct mp_filter* error_handler; } ;

/* Variables and functions */

void mp_filter_set_error_handler(struct mp_filter *f, struct mp_filter *handler)
{
    f->in->error_handler = handler;
}