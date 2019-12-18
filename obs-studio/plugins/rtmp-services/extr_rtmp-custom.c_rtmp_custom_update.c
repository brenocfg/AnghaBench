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
struct rtmp_custom {void* password; void* username; int /*<<< orphan*/  use_auth; void* key; void* server; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (void*) ; 
 void* bstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_get_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void rtmp_custom_update(void *data, obs_data_t *settings)
{
	struct rtmp_custom *service = data;

	bfree(service->server);
	bfree(service->key);

	service->server = bstrdup(obs_data_get_string(settings, "server"));
	service->key = bstrdup(obs_data_get_string(settings, "key"));
	service->use_auth = obs_data_get_bool(settings, "use_auth");
	service->username = bstrdup(obs_data_get_string(settings, "username"));
	service->password = bstrdup(obs_data_get_string(settings, "password"));
}