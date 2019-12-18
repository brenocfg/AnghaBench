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
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_integer_value (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_array (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_false (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_integer (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_object (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_real (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_string (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_real_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_string_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_add_json_array (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_add_json_object (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_bool (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  obs_data_set_double (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_set_int (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void obs_data_add_json_item(obs_data_t *data, const char *key,
				   json_t *json)
{
	if (json_is_object(json))
		obs_data_add_json_object(data, key, json);
	else if (json_is_array(json))
		obs_data_add_json_array(data, key, json);
	else if (json_is_string(json))
		obs_data_set_string(data, key, json_string_value(json));
	else if (json_is_integer(json))
		obs_data_set_int(data, key, json_integer_value(json));
	else if (json_is_real(json))
		obs_data_set_double(data, key, json_real_value(json));
	else if (json_is_true(json))
		obs_data_set_bool(data, key, true);
	else if (json_is_false(json))
		obs_data_set_bool(data, key, false);
}