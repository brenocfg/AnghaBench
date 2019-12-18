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
struct fscache_cookie_def {int type; int /*<<< orphan*/ * name; } ;
struct fscache_cookie {int type; int /*<<< orphan*/  flags; int /*<<< orphan*/  n_children; TYPE_1__* def; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_ENABLED ; 
#define  FSCACHE_COOKIE_TYPE_DATAFILE 129 
#define  FSCACHE_COOKIE_TYPE_INDEX 128 
 int /*<<< orphan*/  _enter (char*,char*,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ fscache_acquire_non_index_cookie (struct fscache_cookie*,int /*<<< orphan*/ ) ; 
 struct fscache_cookie* fscache_alloc_cookie (struct fscache_cookie*,struct fscache_cookie_def const*,void const*,size_t,void const*,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_cookie_discard ; 
 int /*<<< orphan*/  fscache_cookie_put (struct fscache_cookie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_cookie_put_acquire_nobufs ; 
 int /*<<< orphan*/  fscache_free_cookie (struct fscache_cookie*) ; 
 struct fscache_cookie* fscache_hash_cookie (struct fscache_cookie*) ; 
 int /*<<< orphan*/  fscache_n_acquires ; 
 int /*<<< orphan*/  fscache_n_acquires_nobufs ; 
 int /*<<< orphan*/  fscache_n_acquires_null ; 
 int /*<<< orphan*/  fscache_n_acquires_ok ; 
 int /*<<< orphan*/  fscache_n_acquires_oom ; 
 int /*<<< orphan*/  fscache_n_cookie_data ; 
 int /*<<< orphan*/  fscache_n_cookie_index ; 
 int /*<<< orphan*/  fscache_n_cookie_special ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_fscache_acquire (struct fscache_cookie*) ; 
 int /*<<< orphan*/  trace_fscache_cookie (struct fscache_cookie*,int /*<<< orphan*/ ,int) ; 

struct fscache_cookie *__fscache_acquire_cookie(
	struct fscache_cookie *parent,
	const struct fscache_cookie_def *def,
	const void *index_key, size_t index_key_len,
	const void *aux_data, size_t aux_data_len,
	void *netfs_data,
	loff_t object_size,
	bool enable)
{
	struct fscache_cookie *candidate, *cookie;

	BUG_ON(!def);

	_enter("{%s},{%s},%p,%u",
	       parent ? (char *) parent->def->name : "<no-parent>",
	       def->name, netfs_data, enable);

	if (!index_key || !index_key_len || index_key_len > 255 || aux_data_len > 255)
		return NULL;
	if (!aux_data || !aux_data_len) {
		aux_data = NULL;
		aux_data_len = 0;
	}

	fscache_stat(&fscache_n_acquires);

	/* if there's no parent cookie, then we don't create one here either */
	if (!parent) {
		fscache_stat(&fscache_n_acquires_null);
		_leave(" [no parent]");
		return NULL;
	}

	/* validate the definition */
	BUG_ON(!def->name[0]);

	BUG_ON(def->type == FSCACHE_COOKIE_TYPE_INDEX &&
	       parent->type != FSCACHE_COOKIE_TYPE_INDEX);

	candidate = fscache_alloc_cookie(parent, def,
					 index_key, index_key_len,
					 aux_data, aux_data_len,
					 netfs_data, object_size);
	if (!candidate) {
		fscache_stat(&fscache_n_acquires_oom);
		_leave(" [ENOMEM]");
		return NULL;
	}

	cookie = fscache_hash_cookie(candidate);
	if (!cookie) {
		trace_fscache_cookie(candidate, fscache_cookie_discard, 1);
		goto out;
	}

	if (cookie == candidate)
		candidate = NULL;

	switch (cookie->type) {
	case FSCACHE_COOKIE_TYPE_INDEX:
		fscache_stat(&fscache_n_cookie_index);
		break;
	case FSCACHE_COOKIE_TYPE_DATAFILE:
		fscache_stat(&fscache_n_cookie_data);
		break;
	default:
		fscache_stat(&fscache_n_cookie_special);
		break;
	}

	trace_fscache_acquire(cookie);

	if (enable) {
		/* if the object is an index then we need do nothing more here
		 * - we create indices on disk when we need them as an index
		 * may exist in multiple caches */
		if (cookie->type != FSCACHE_COOKIE_TYPE_INDEX) {
			if (fscache_acquire_non_index_cookie(cookie, object_size) == 0) {
				set_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags);
			} else {
				atomic_dec(&parent->n_children);
				fscache_cookie_put(cookie,
						   fscache_cookie_put_acquire_nobufs);
				fscache_stat(&fscache_n_acquires_nobufs);
				_leave(" = NULL");
				return NULL;
			}
		} else {
			set_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags);
		}
	}

	fscache_stat(&fscache_n_acquires_ok);

out:
	fscache_free_cookie(candidate);
	return cookie;
}