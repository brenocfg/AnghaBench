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
struct ao {TYPE_1__* api; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* uninit ) (struct ao*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ao*) ; 
 int /*<<< orphan*/  talloc_free (struct ao*) ; 

void ao_uninit(struct ao *ao)
{
    if (ao)
        ao->api->uninit(ao);
    talloc_free(ao);
}