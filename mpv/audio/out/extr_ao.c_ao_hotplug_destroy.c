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
struct ao_hotplug {struct ao_hotplug* ao; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hotplug_uninit ) (struct ao_hotplug*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ao_hotplug*) ; 
 int /*<<< orphan*/  talloc_free (struct ao_hotplug*) ; 

void ao_hotplug_destroy(struct ao_hotplug *hp)
{
    if (!hp)
        return;
    if (hp->ao && hp->ao->driver->hotplug_uninit)
        hp->ao->driver->hotplug_uninit(hp->ao);
    talloc_free(hp->ao);
    talloc_free(hp);
}