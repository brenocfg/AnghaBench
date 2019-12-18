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
struct rtmp_common {int /*<<< orphan*/ * output; int /*<<< orphan*/ * service; int /*<<< orphan*/ * key; int /*<<< orphan*/ * server; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 void* bstrdup (char const*) ; 
 int /*<<< orphan*/  ensure_valid_url (struct rtmp_common*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_service (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 char* get_string_val (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 scalar_t__ json_is_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * open_services_file () ; 

__attribute__((used)) static void rtmp_common_update(void *data, obs_data_t *settings)
{
	struct rtmp_common *service = data;

	bfree(service->service);
	bfree(service->server);
	bfree(service->output);
	bfree(service->key);

	service->service = bstrdup(obs_data_get_string(settings, "service"));
	service->server = bstrdup(obs_data_get_string(settings, "server"));
	service->key = bstrdup(obs_data_get_string(settings, "key"));
	service->output = NULL;

	json_t *root = open_services_file();
	if (root) {
		const char *new_name;
		json_t *serv = find_service(root, service->service, &new_name);

		if (new_name) {
			bfree(service->service);
			service->service = bstrdup(new_name);
		}

		if (serv) {
			json_t *rec = json_object_get(serv, "recommended");
			if (json_is_object(rec)) {
				const char *out = get_string_val(rec, "output");
				if (out)
					service->output = bstrdup(out);
			}

			ensure_valid_url(service, serv, settings);
		}
	}
	json_decref(root);

	if (!service->output)
		service->output = bstrdup("rtmp_output");
}