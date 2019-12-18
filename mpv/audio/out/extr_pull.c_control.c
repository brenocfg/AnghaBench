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
struct ao {TYPE_1__* driver; } ;
typedef  enum aocontrol { ____Placeholder_aocontrol } aocontrol ;
struct TYPE_2__ {int (* control ) (struct ao*,int,void*) ;} ;

/* Variables and functions */
 int CONTROL_UNKNOWN ; 
 int stub1 (struct ao*,int,void*) ; 

__attribute__((used)) static int control(struct ao *ao, enum aocontrol cmd, void *arg)
{
    if (ao->driver->control)
        return ao->driver->control(ao, cmd, arg);
    return CONTROL_UNKNOWN;
}