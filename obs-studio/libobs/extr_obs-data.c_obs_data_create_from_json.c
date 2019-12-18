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
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {int /*<<< orphan*/  text; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_REJECT_DUPLICATES ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  obs_data_add_json_object_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 

obs_data_t *obs_data_create_from_json(const char *json_string)
{
	obs_data_t *data = obs_data_create();

	json_error_t error;
	json_t *root = json_loads(json_string, JSON_REJECT_DUPLICATES, &error);

	if (root) {
		obs_data_add_json_object_data(data, root);
		json_decref(root);
	} else {
		blog(LOG_ERROR,
		     "obs-data.c: [obs_data_create_from_json] "
		     "Failed reading json string (%d): %s",
		     error.line, error.text);
		obs_data_release(data);
		data = NULL;
	}

	return data;
}