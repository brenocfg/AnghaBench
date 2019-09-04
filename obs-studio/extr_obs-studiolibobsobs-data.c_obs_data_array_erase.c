#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * array; } ;
struct TYPE_4__ {TYPE_3__ objects; } ;
typedef  TYPE_1__ obs_data_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_erase (TYPE_3__,size_t) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ ) ; 

void obs_data_array_erase(obs_data_array_t *array, size_t idx)
{
	if (array) {
		obs_data_release(array->objects.array[idx]);
		da_erase(array->objects, idx);
	}
}