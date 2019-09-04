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
struct mp_filter {struct chain* priv; } ;
struct TYPE_2__ {int ao_needs_update; int got_output_eof; } ;
struct chain {TYPE_1__ public; } ;

/* Variables and functions */

__attribute__((used)) static void reset(struct mp_filter *f)
{
    struct chain *p = f->priv;

    p->public.ao_needs_update = false;

    p->public.got_output_eof = false;
}