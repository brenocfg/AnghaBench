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
struct list_data {int dummy; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 struct list_data* get_list_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_data_free (struct list_data*) ; 

void obs_property_list_clear(obs_property_t *p)
{
	struct list_data *data = get_list_data(p);
	if (data)
		list_data_free(data);
}