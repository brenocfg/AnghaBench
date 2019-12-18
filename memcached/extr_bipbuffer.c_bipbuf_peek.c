#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; scalar_t__ a_start; scalar_t__ data; } ;
typedef  TYPE_1__ bipbuf_t ;

/* Variables and functions */
 scalar_t__ bipbuf_is_empty (TYPE_1__ const*) ; 

unsigned char *bipbuf_peek(const bipbuf_t* me, const unsigned int size)
{
    /* make sure we can actually peek at this data */
    if (me->size < me->a_start + size)
        return NULL;

    if (bipbuf_is_empty(me))
        return NULL;

    return (unsigned char *)me->data + me->a_start;
}