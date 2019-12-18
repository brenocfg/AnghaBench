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
struct TYPE_3__ {float rot; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */

float obs_sceneitem_get_rot(const obs_sceneitem_t *item)
{
	return item ? item->rot : 0.0f;
}