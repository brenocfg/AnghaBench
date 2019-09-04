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
struct TYPE_3__ {int a_end; int a_start; int b_end; } ;
typedef  TYPE_1__ bipbuf_t ;

/* Variables and functions */

int bipbuf_used(const bipbuf_t* me)
{
    return (me->a_end - me->a_start) + me->b_end;
}