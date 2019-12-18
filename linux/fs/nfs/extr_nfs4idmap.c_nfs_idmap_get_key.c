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
struct user_key_payload {size_t datalen; int /*<<< orphan*/  data; int /*<<< orphan*/  perm; } ;
typedef  struct key {size_t datalen; int /*<<< orphan*/  data; int /*<<< orphan*/  perm; } const key ;
struct idmap {int dummy; } ;
struct cred {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ IS_ERR (struct user_key_payload const*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct user_key_payload const*) ; 
 int /*<<< orphan*/  KEY_USR_VIEW ; 
 size_t PTR_ERR (struct user_key_payload const*) ; 
 int /*<<< orphan*/  id_resolver_cache ; 
 int /*<<< orphan*/  key_put (struct user_key_payload const*) ; 
 size_t key_validate (struct user_key_payload const*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 struct user_key_payload* nfs_idmap_request_key (char const*,size_t,char const*,struct idmap*) ; 
 struct cred* override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 struct user_key_payload* user_key_payload_rcu (struct user_key_payload const*) ; 

__attribute__((used)) static ssize_t nfs_idmap_get_key(const char *name, size_t namelen,
				 const char *type, void *data,
				 size_t data_size, struct idmap *idmap)
{
	const struct cred *saved_cred;
	struct key *rkey;
	const struct user_key_payload *payload;
	ssize_t ret;

	saved_cred = override_creds(id_resolver_cache);
	rkey = nfs_idmap_request_key(name, namelen, type, idmap);
	revert_creds(saved_cred);

	if (IS_ERR(rkey)) {
		ret = PTR_ERR(rkey);
		goto out;
	}

	rcu_read_lock();
	rkey->perm |= KEY_USR_VIEW;

	ret = key_validate(rkey);
	if (ret < 0)
		goto out_up;

	payload = user_key_payload_rcu(rkey);
	if (IS_ERR_OR_NULL(payload)) {
		ret = PTR_ERR(payload);
		goto out_up;
	}

	ret = payload->datalen;
	if (ret > 0 && ret <= data_size)
		memcpy(data, payload->data, ret);
	else
		ret = -EINVAL;

out_up:
	rcu_read_unlock();
	key_put(rkey);
out:
	return ret;
}