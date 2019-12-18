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
struct update_info {char const* temp; int thread_created; int /*<<< orphan*/  thread; void* param; int /*<<< orphan*/  callback; int /*<<< orphan*/  url; void* cache; void* local; void* user_agent; void* log_prefix; } ;
typedef  struct update_info update_info_t ;
struct dstr {char const* array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  confirm_file_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 void* bstrdup (char const*) ; 
 struct update_info* bzalloc (int) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_cat_ch (struct dstr*,char) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 char dstr_end (struct dstr*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  get_path (char const*,char*) ; 
 scalar_t__ os_mkdir (char const*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct update_info*) ; 
 int /*<<< orphan*/  update_thread ; 

update_info_t *update_info_create(const char *log_prefix,
				  const char *user_agent,
				  const char *update_url, const char *local_dir,
				  const char *cache_dir,
				  confirm_file_callback_t confirm_callback,
				  void *param)
{
	struct update_info *info;
	struct dstr dir = {0};

	if (!log_prefix)
		log_prefix = "";

	if (os_mkdir(cache_dir) < 0) {
		blog(LOG_WARNING, "%sCould not create cache directory %s",
		     log_prefix, cache_dir);
		return NULL;
	}

	dstr_copy(&dir, cache_dir);
	if (dstr_end(&dir) != '/' && dstr_end(&dir) != '\\')
		dstr_cat_ch(&dir, '/');
	dstr_cat(&dir, ".temp");

	if (os_mkdir(dir.array) < 0) {
		blog(LOG_WARNING, "%sCould not create temp directory %s",
		     log_prefix, cache_dir);
		dstr_free(&dir);
		return NULL;
	}

	info = bzalloc(sizeof(*info));
	info->log_prefix = bstrdup(log_prefix);
	info->user_agent = bstrdup(user_agent);
	info->temp = dir.array;
	info->local = bstrdup(local_dir);
	info->cache = bstrdup(cache_dir);
	info->url = get_path(update_url, "package.json");
	info->callback = confirm_callback;
	info->param = param;

	if (pthread_create(&info->thread, NULL, update_thread, info) == 0)
		info->thread_created = true;

	return info;
}