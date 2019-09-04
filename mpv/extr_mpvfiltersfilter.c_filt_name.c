#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_filter {TYPE_2__* in; } ;
struct TYPE_4__ {TYPE_1__* info; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */

__attribute__((used)) static const char *filt_name(struct mp_filter *f)
{
    return f ? f->in->info->name : "-";
}