#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dstr {char* array; int len; } ;
struct TYPE_5__ {size_t num; } ;
struct config_section {char* name; TYPE_2__ items; } ;
struct config_item {char* value; char* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; TYPE_2__ sections; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ config_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CONFIG_ERROR ; 
 int CONFIG_FILENOTFOUND ; 
 int CONFIG_SUCCESS ; 
 void* darray_item (int,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int config_save(config_t *config)
{
	FILE *f;
	struct dstr str, tmp;
	size_t i, j;
	int ret = CONFIG_ERROR;

	if (!config)
		return CONFIG_ERROR;
	if (!config->file)
		return CONFIG_ERROR;

	dstr_init(&str);
	dstr_init(&tmp);

	pthread_mutex_lock(&config->mutex);

	f = os_fopen(config->file, "wb");
	if (!f) {
		pthread_mutex_unlock(&config->mutex);
		return CONFIG_FILENOTFOUND;
	}

	for (i = 0; i < config->sections.num; i++) {
		struct config_section *section = darray_item(
			sizeof(struct config_section), &config->sections, i);

		if (i)
			dstr_cat(&str, "\n");

		dstr_cat(&str, "[");
		dstr_cat(&str, section->name);
		dstr_cat(&str, "]\n");

		for (j = 0; j < section->items.num; j++) {
			struct config_item *item = darray_item(
				sizeof(struct config_item), &section->items, j);

			dstr_copy(&tmp, item->value ? item->value : "");
			dstr_replace(&tmp, "\\", "\\\\");
			dstr_replace(&tmp, "\r", "\\r");
			dstr_replace(&tmp, "\n", "\\n");

			dstr_cat(&str, item->name);
			dstr_cat(&str, "=");
			dstr_cat(&str, tmp.array);
			dstr_cat(&str, "\n");
		}
	}

#ifdef _WIN32
	if (fwrite("\xEF\xBB\xBF", 3, 1, f) != 1)
		goto cleanup;
#endif
	if (fwrite(str.array, str.len, 1, f) != 1)
		goto cleanup;

	ret = CONFIG_SUCCESS;

cleanup:
	fclose(f);

	pthread_mutex_unlock(&config->mutex);

	dstr_free(&tmp);
	dstr_free(&str);

	return ret;
}