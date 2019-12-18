#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* jsonsl_t ;
struct TYPE_3__ {int can_insert; scalar_t__ expecting; scalar_t__ in_escape; scalar_t__ stopfl; scalar_t__ level; scalar_t__ pos; scalar_t__ tok_last; } ;

/* Variables and functions */

void jsonsl_reset(jsonsl_t jsn)
{
    jsn->tok_last = 0;
    jsn->can_insert = 1;
    jsn->pos = 0;
    jsn->level = 0;
    jsn->stopfl = 0;
    jsn->in_escape = 0;
    jsn->expecting = 0;
}