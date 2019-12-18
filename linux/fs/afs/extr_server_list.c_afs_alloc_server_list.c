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
typedef  int u8 ;
struct key {int dummy; } ;
struct afs_vldb_entry {int nr_servers; int* fs_mask; int /*<<< orphan*/ * fs_server; } ;
struct afs_server_list {int nr_servers; TYPE_1__* servers; int /*<<< orphan*/  lock; int /*<<< orphan*/  usage; } ;
struct afs_server_entry {int dummy; } ;
struct afs_server {int /*<<< orphan*/  uuid; } ;
struct afs_cell {int /*<<< orphan*/  net; } ;
struct TYPE_3__ {struct afs_server* server; } ;

/* Variables and functions */
 int EDESTADDRREQ ; 
 int ENOENT ; 
 int ENOMEDIUM ; 
 int ENOMEM ; 
 struct afs_server_list* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct afs_server*) ; 
 int PTR_ERR (struct afs_server*) ; 
 struct afs_server* afs_lookup_server (struct afs_cell*,struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_put_server (int /*<<< orphan*/ ,struct afs_server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_put_serverlist (int /*<<< orphan*/ ,struct afs_server_list*) ; 
 int /*<<< orphan*/  afs_server_trace_put_slist_isort ; 
 struct afs_server_list* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  servers ; 
 int /*<<< orphan*/  struct_size (struct afs_server_list*,int /*<<< orphan*/ ,int) ; 

struct afs_server_list *afs_alloc_server_list(struct afs_cell *cell,
					      struct key *key,
					      struct afs_vldb_entry *vldb,
					      u8 type_mask)
{
	struct afs_server_list *slist;
	struct afs_server *server;
	int ret = -ENOMEM, nr_servers = 0, i, j;

	for (i = 0; i < vldb->nr_servers; i++)
		if (vldb->fs_mask[i] & type_mask)
			nr_servers++;

	slist = kzalloc(struct_size(slist, servers, nr_servers), GFP_KERNEL);
	if (!slist)
		goto error;

	refcount_set(&slist->usage, 1);
	rwlock_init(&slist->lock);

	/* Make sure a records exists for each server in the list. */
	for (i = 0; i < vldb->nr_servers; i++) {
		if (!(vldb->fs_mask[i] & type_mask))
			continue;

		server = afs_lookup_server(cell, key, &vldb->fs_server[i]);
		if (IS_ERR(server)) {
			ret = PTR_ERR(server);
			if (ret == -ENOENT ||
			    ret == -ENOMEDIUM)
				continue;
			goto error_2;
		}

		/* Insertion-sort by UUID */
		for (j = 0; j < slist->nr_servers; j++)
			if (memcmp(&slist->servers[j].server->uuid,
				   &server->uuid,
				   sizeof(server->uuid)) >= 0)
				break;
		if (j < slist->nr_servers) {
			if (slist->servers[j].server == server) {
				afs_put_server(cell->net, server,
					       afs_server_trace_put_slist_isort);
				continue;
			}

			memmove(slist->servers + j + 1,
				slist->servers + j,
				(slist->nr_servers - j) * sizeof(struct afs_server_entry));
		}

		slist->servers[j].server = server;
		slist->nr_servers++;
	}

	if (slist->nr_servers == 0) {
		ret = -EDESTADDRREQ;
		goto error_2;
	}

	return slist;

error_2:
	afs_put_serverlist(cell->net, slist);
error:
	return ERR_PTR(ret);
}