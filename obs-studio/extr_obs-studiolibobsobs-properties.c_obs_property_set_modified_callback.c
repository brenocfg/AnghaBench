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
struct TYPE_3__ {int /*<<< orphan*/  modified; } ;
typedef  TYPE_1__ obs_property_t ;
typedef  int /*<<< orphan*/  obs_property_modified_t ;

/* Variables and functions */

void obs_property_set_modified_callback(obs_property_t *p,
		obs_property_modified_t modified)
{
	if (p) p->modified = modified;
}