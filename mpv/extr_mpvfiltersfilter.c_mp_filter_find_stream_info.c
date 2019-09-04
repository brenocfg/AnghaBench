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
struct mp_stream_info {int dummy; } ;
struct mp_filter {TYPE_1__* in; struct mp_stream_info* stream_info; } ;
struct TYPE_2__ {struct mp_filter* parent; } ;

/* Variables and functions */

struct mp_stream_info *mp_filter_find_stream_info(struct mp_filter *f)
{
    while (f) {
        if (f->stream_info)
            return f->stream_info;
        f = f->in->parent;
    }
    return NULL;
}