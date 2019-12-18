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
struct update_info {int /*<<< orphan*/  etag_remote; int /*<<< orphan*/  cache; } ;
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/ * obs_data_create () ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_save_json (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_data_set_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_save_metadata(struct update_info *info)
{
	struct dstr path = {0};

	if (!info->etag_remote)
		return;

	dstr_copy(&path, info->cache);
	dstr_cat(&path, "meta.json");

	obs_data_t *data;
	data = obs_data_create();
	obs_data_set_string(data, "etag", info->etag_remote);
	obs_data_save_json(data, path.array);
	obs_data_release(data);

	dstr_free(&path);
}