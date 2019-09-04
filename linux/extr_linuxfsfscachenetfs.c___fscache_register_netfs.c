#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fscache_netfs {int /*<<< orphan*/  name; struct fscache_cookie* primary_index; int /*<<< orphan*/  version; } ;
struct fscache_cookie {int flags; TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  n_children; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int FSCACHE_COOKIE_ENABLED ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct fscache_cookie* fscache_alloc_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct fscache_netfs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_cookie_discard ; 
 int /*<<< orphan*/  fscache_cookie_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_cookie_get_register_netfs ; 
 int /*<<< orphan*/  fscache_cookie_put (struct fscache_cookie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_cookie_put_dup_netfs ; 
 int /*<<< orphan*/  fscache_free_cookie (struct fscache_cookie*) ; 
 int /*<<< orphan*/  fscache_fsdef_index ; 
 int /*<<< orphan*/  fscache_fsdef_netfs_def ; 
 struct fscache_cookie* fscache_hash_cookie (struct fscache_cookie*) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_fscache_cookie (struct fscache_cookie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_fscache_netfs (struct fscache_netfs*) ; 

int __fscache_register_netfs(struct fscache_netfs *netfs)
{
	struct fscache_cookie *candidate, *cookie;

	_enter("{%s}", netfs->name);

	/* allocate a cookie for the primary index */
	candidate = fscache_alloc_cookie(&fscache_fsdef_index,
					 &fscache_fsdef_netfs_def,
					 netfs->name, strlen(netfs->name),
					 &netfs->version, sizeof(netfs->version),
					 netfs, 0);
	if (!candidate) {
		_leave(" = -ENOMEM");
		return -ENOMEM;
	}

	candidate->flags = 1 << FSCACHE_COOKIE_ENABLED;

	/* check the netfs type is not already present */
	cookie = fscache_hash_cookie(candidate);
	if (!cookie)
		goto already_registered;
	if (cookie != candidate) {
		trace_fscache_cookie(candidate, fscache_cookie_discard, 1);
		fscache_free_cookie(candidate);
	}

	fscache_cookie_get(cookie->parent, fscache_cookie_get_register_netfs);
	atomic_inc(&cookie->parent->n_children);

	netfs->primary_index = cookie;

	pr_notice("Netfs '%s' registered for caching\n", netfs->name);
	trace_fscache_netfs(netfs);
	_leave(" = 0");
	return 0;

already_registered:
	fscache_cookie_put(candidate, fscache_cookie_put_dup_netfs);
	_leave(" = -EEXIST");
	return -EEXIST;
}