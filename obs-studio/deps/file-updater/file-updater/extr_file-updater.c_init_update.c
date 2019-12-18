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
struct update_info {char const* user_agent; void* header; int /*<<< orphan*/  etag_local; int /*<<< orphan*/  cache; void* cache_package; int /*<<< orphan*/  local; void* local_package; int /*<<< orphan*/  curl; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  bstrdup (char const*) ; 
 int /*<<< orphan*/  curl_easy_init () ; 
 void* curl_slist_append (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 void* get_package (int /*<<< orphan*/ ,char*) ; 
 char* obs_data_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static bool init_update(struct update_info *info)
{
	struct dstr user_agent = {0};

	info->curl = curl_easy_init();
	if (!info->curl) {
		warn("Could not initialize Curl");
		return false;
	}

	info->local_package = get_package(info->local, "package.json");
	info->cache_package = get_package(info->cache, "package.json");

	obs_data_t *metadata = get_package(info->cache, "meta.json");
	if (metadata) {
		const char *etag = obs_data_get_string(metadata, "etag");
		if (etag) {
			struct dstr if_none_match = {0};
			dstr_copy(&if_none_match, "If-None-Match: ");
			dstr_cat(&if_none_match, etag);

			info->etag_local = bstrdup(etag);

			info->header = curl_slist_append(info->header,
							 if_none_match.array);

			dstr_free(&if_none_match);
		}

		obs_data_release(metadata);
	}

	dstr_copy(&user_agent, "User-Agent: ");
	dstr_cat(&user_agent, info->user_agent);

	info->header = curl_slist_append(info->header, user_agent.array);

	dstr_free(&user_agent);
	return true;
}