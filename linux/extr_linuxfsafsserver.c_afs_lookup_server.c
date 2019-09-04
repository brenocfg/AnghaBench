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
typedef  int /*<<< orphan*/  uuid_t ;
struct key {int dummy; } ;
struct afs_server {int /*<<< orphan*/  usage; } ;
struct afs_cell {int /*<<< orphan*/  net; } ;
struct afs_addr_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct afs_server* ERR_CAST (struct afs_addr_list*) ; 
 struct afs_server* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct afs_addr_list*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _leave (char*,struct afs_server*,int /*<<< orphan*/ ) ; 
 struct afs_server* afs_alloc_server (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct afs_addr_list*) ; 
 struct afs_server* afs_find_server_by_uuid (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct afs_server* afs_install_server (int /*<<< orphan*/ ,struct afs_server*) ; 
 int /*<<< orphan*/  afs_put_addrlist (struct afs_addr_list*) ; 
 struct afs_addr_list* afs_vl_lookup_addrs (struct afs_cell*,struct key*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct afs_server*) ; 

struct afs_server *afs_lookup_server(struct afs_cell *cell, struct key *key,
				     const uuid_t *uuid)
{
	struct afs_addr_list *alist;
	struct afs_server *server, *candidate;

	_enter("%p,%pU", cell->net, uuid);

	server = afs_find_server_by_uuid(cell->net, uuid);
	if (server)
		return server;

	alist = afs_vl_lookup_addrs(cell, key, uuid);
	if (IS_ERR(alist))
		return ERR_CAST(alist);

	candidate = afs_alloc_server(cell->net, uuid, alist);
	if (!candidate) {
		afs_put_addrlist(alist);
		return ERR_PTR(-ENOMEM);
	}

	server = afs_install_server(cell->net, candidate);
	if (server != candidate) {
		afs_put_addrlist(alist);
		kfree(candidate);
	}

	_leave(" = %p{%d}", server, atomic_read(&server->usage));
	return server;
}