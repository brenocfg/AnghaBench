#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ obs_data_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_item_destroy (TYPE_1__*) ; 
 long os_atomic_dec_long (int /*<<< orphan*/ *) ; 

void obs_data_item_release(obs_data_item_t **item)
{
	if (item && *item) {
		long ref = os_atomic_dec_long(&(*item)->ref);
		if (!ref) {
			obs_data_item_destroy(*item);
			*item = NULL;
		}
	}
}