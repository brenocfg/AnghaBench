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
typedef  int /*<<< orphan*/  obs_data_item_t ;
typedef  char const* (* get_data_t ) (int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_DATA_STRING ; 
 scalar_t__ item_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *data_item_get_string(obs_data_item_t *item,
					       get_data_t get_data)
{
	return item_valid(item, OBS_DATA_STRING) && get_data(item)
		       ? get_data(item)
		       : "";
}