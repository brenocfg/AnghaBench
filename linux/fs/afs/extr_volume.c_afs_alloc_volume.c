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
struct afs_volume {size_t type; int /*<<< orphan*/  cell; struct afs_server_list* servers; int /*<<< orphan*/  name; int /*<<< orphan*/  cb_v_break_lock; int /*<<< orphan*/  servers_lock; int /*<<< orphan*/  proc_link; int /*<<< orphan*/  usage; scalar_t__ name_len; int /*<<< orphan*/  type_force; scalar_t__ update_at; int /*<<< orphan*/  vid; } ;
struct afs_vldb_entry {int nr_servers; unsigned long* fs_mask; scalar_t__ name_len; int /*<<< orphan*/  name; int /*<<< orphan*/ * vid; } ;
struct afs_server_list {int /*<<< orphan*/  usage; } ;
struct afs_fs_context {size_t type; int /*<<< orphan*/  net; int /*<<< orphan*/  key; int /*<<< orphan*/  cell; int /*<<< orphan*/  force; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct afs_volume* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct afs_server_list*) ; 
 int PTR_ERR (struct afs_server_list*) ; 
 struct afs_server_list* afs_alloc_server_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct afs_vldb_entry*,unsigned long) ; 
 int /*<<< orphan*/  afs_get_cell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_put_cell (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ afs_volume_record_life ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct afs_volume*) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 struct afs_volume* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct afs_volume *afs_alloc_volume(struct afs_fs_context *params,
					   struct afs_vldb_entry *vldb,
					   unsigned long type_mask)
{
	struct afs_server_list *slist;
	struct afs_volume *volume;
	int ret = -ENOMEM, nr_servers = 0, i;

	for (i = 0; i < vldb->nr_servers; i++)
		if (vldb->fs_mask[i] & type_mask)
			nr_servers++;

	volume = kzalloc(sizeof(struct afs_volume), GFP_KERNEL);
	if (!volume)
		goto error_0;

	volume->vid		= vldb->vid[params->type];
	volume->update_at	= ktime_get_real_seconds() + afs_volume_record_life;
	volume->cell		= afs_get_cell(params->cell);
	volume->type		= params->type;
	volume->type_force	= params->force;
	volume->name_len	= vldb->name_len;

	atomic_set(&volume->usage, 1);
	INIT_LIST_HEAD(&volume->proc_link);
	rwlock_init(&volume->servers_lock);
	rwlock_init(&volume->cb_v_break_lock);
	memcpy(volume->name, vldb->name, vldb->name_len + 1);

	slist = afs_alloc_server_list(params->cell, params->key, vldb, type_mask);
	if (IS_ERR(slist)) {
		ret = PTR_ERR(slist);
		goto error_1;
	}

	refcount_set(&slist->usage, 1);
	volume->servers = slist;
	return volume;

error_1:
	afs_put_cell(params->net, volume->cell);
	kfree(volume);
error_0:
	return ERR_PTR(ret);
}