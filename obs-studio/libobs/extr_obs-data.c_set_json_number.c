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
typedef  int /*<<< orphan*/  json_t ;
typedef  enum obs_data_number_type { ____Placeholder_obs_data_number_type } obs_data_number_type ;

/* Variables and functions */
 int OBS_DATA_NUM_INT ; 
 int /*<<< orphan*/  json_integer (long long) ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_real (double) ; 
 double obs_data_item_get_double (int /*<<< orphan*/ *) ; 
 long long obs_data_item_get_int (int /*<<< orphan*/ *) ; 
 int obs_data_item_numtype (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void set_json_number(json_t *json, const char *name,
				   obs_data_item_t *item)
{
	enum obs_data_number_type type = obs_data_item_numtype(item);

	if (type == OBS_DATA_NUM_INT) {
		long long val = obs_data_item_get_int(item);
		json_object_set_new(json, name, json_integer(val));
	} else {
		double val = obs_data_item_get_double(item);
		json_object_set_new(json, name, json_real(val));
	}
}