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
struct ingest {int /*<<< orphan*/  url; int /*<<< orphan*/  name; int /*<<< orphan*/  member_0; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {scalar_t__ num; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  bstrdup (char const*) ; 
 TYPE_1__ cur_ingests ; 
 int /*<<< orphan*/  da_push_back (TYPE_1__,struct ingest*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  free_ingests () ; 
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,size_t) ; 
 size_t json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 char* json_string_value (int /*<<< orphan*/ *) ; 
 char* obs_module_config_path (char*) ; 
 int /*<<< orphan*/  os_quick_write_utf8_file (char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_safe_replace (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static bool load_ingests(const char *json, bool write_file)
{
	json_t *root;
	json_t *ingests;
	bool success = false;
	char *cache_old;
	char *cache_new;
	size_t count;

	root = json_loads(json, 0, NULL);
	if (!root)
		goto finish;

	ingests = json_object_get(root, "ingests");
	if (!ingests)
		goto finish;

	count = json_array_size(ingests);
	if (count <= 1 && cur_ingests.num)
		goto finish;

	free_ingests();

	for (size_t i = 0; i < count; i++) {
		json_t *item = json_array_get(ingests, i);
		json_t *item_name = json_object_get(item, "name");
		json_t *item_url = json_object_get(item, "url_template");
		struct ingest ingest = {0};
		struct dstr url = {0};

		if (!item_name || !item_url)
			continue;

		const char *url_str = json_string_value(item_url);
		const char *name_str = json_string_value(item_name);

		/* At the moment they currently mis-spell "deprecated",
		 * but that may change in the future, so blacklist both */
		if (strstr(name_str, "deprecated") != NULL ||
		    strstr(name_str, "depracated") != NULL)
			continue;

		dstr_copy(&url, url_str);
		dstr_replace(&url, "/{stream_key}", "");

		ingest.name = bstrdup(name_str);
		ingest.url = url.array;

		da_push_back(cur_ingests, &ingest);
	}

	if (!cur_ingests.num)
		goto finish;

	success = true;

	if (!write_file)
		goto finish;

	cache_old = obs_module_config_path("twitch_ingests.json");
	cache_new = obs_module_config_path("twitch_ingests.new.json");

	os_quick_write_utf8_file(cache_new, json, strlen(json), false);
	os_safe_replace(cache_old, cache_new, NULL);

	bfree(cache_old);
	bfree(cache_new);

finish:
	if (root)
		json_decref(root);
	return success;
}