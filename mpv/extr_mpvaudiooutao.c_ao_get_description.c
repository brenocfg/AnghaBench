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
struct TYPE_2__ {char const* description; } ;

/* Variables and functions */

const char *ao_get_description(struct ao *ao)
{
    return ao->driver->description;
}