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
struct TYPE_3__ {int /*<<< orphan*/ * desc; } ;
typedef  TYPE_1__ obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bstrdup (char const*) ; 

void obs_property_set_description(obs_property_t *p, const char *description)
{
	if (p) {
		bfree(p->desc);
		p->desc = description && *description ? bstrdup(description)
						      : NULL;
	}
}