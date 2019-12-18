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
struct TYPE_4__ {char const* json; } ;
typedef  TYPE_1__ obs_data_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int JSON_INDENT (int) ; 
 int JSON_PRESERVE_ORDER ; 
 int /*<<< orphan*/  free (char const*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char const* json_dumps (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * obs_data_to_json (TYPE_1__*) ; 

const char *obs_data_get_json(obs_data_t *data)
{
	if (!data)
		return NULL;

	/* NOTE: don't use libobs bfree for json text */
	free(data->json);
	data->json = NULL;

	json_t *root = obs_data_to_json(data);
	data->json = json_dumps(root, JSON_PRESERVE_ORDER | JSON_INDENT(4));
	json_decref(root);

	return data->json;
}