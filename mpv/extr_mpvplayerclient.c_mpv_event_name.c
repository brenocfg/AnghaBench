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
typedef  size_t mpv_event_id ;

/* Variables and functions */
 unsigned int MP_ARRAY_SIZE (char const**) ; 
 char const** event_table ; 

const char *mpv_event_name(mpv_event_id event)
{
    if ((unsigned)event >= MP_ARRAY_SIZE(event_table))
        return NULL;
    return event_table[event];
}