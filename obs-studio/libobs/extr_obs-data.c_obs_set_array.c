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
typedef  int /*<<< orphan*/  (* set_item_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_item_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_DATA_ARRAY ; 

__attribute__((used)) static inline void obs_set_array(obs_data_t *data, obs_data_item_t **item,
				 const char *name, obs_data_array_t *array,
				 set_item_t set_item_)
{
	set_item_(data, item, name, &array, sizeof(obs_data_t *),
		  OBS_DATA_ARRAY);
}