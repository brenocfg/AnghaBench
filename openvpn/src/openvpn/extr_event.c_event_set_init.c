#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct event_set {int dummy; } ;

/* Variables and functions */
 unsigned int EVENT_METHOD_FAST ; 
 struct event_set* event_set_init_scalable (int*,unsigned int) ; 
 struct event_set* event_set_init_simple (int*,unsigned int) ; 

struct event_set *
event_set_init(int *maxevents, unsigned int flags)
{
    if (flags & EVENT_METHOD_FAST)
    {
        return event_set_init_simple(maxevents, flags);
    }
    else
    {
        return event_set_init_scalable(maxevents, flags);
    }
}