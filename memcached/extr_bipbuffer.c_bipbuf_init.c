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
struct TYPE_3__ {unsigned int size; scalar_t__ b_inuse; scalar_t__ b_end; scalar_t__ a_end; scalar_t__ a_start; } ;
typedef  TYPE_1__ bipbuf_t ;

/* Variables and functions */

void bipbuf_init(bipbuf_t* me, const unsigned int size)
{
    me->a_start = me->a_end = me->b_end = 0;
    me->size = size;
    me->b_inuse = 0;
}