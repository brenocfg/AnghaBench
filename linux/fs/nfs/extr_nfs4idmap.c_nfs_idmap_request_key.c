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
struct key {int /*<<< orphan*/  flags; } ;
struct idmap {int /*<<< orphan*/  idmap_mutex; TYPE_1__* cred; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/ * user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_FLAG_ROOT_CAN_INVAL ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  key_type_id_resolver ; 
 int /*<<< orphan*/  key_type_id_resolver_legacy ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_idmap_get_desc (char const*,size_t,char const*,int /*<<< orphan*/ ,char**) ; 
 struct key* request_key (int /*<<< orphan*/ *,char*,char*) ; 
 struct key* request_key_with_auxdata (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct idmap*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct key *nfs_idmap_request_key(const char *name, size_t namelen,
					 const char *type, struct idmap *idmap)
{
	char *desc;
	struct key *rkey = ERR_PTR(-EAGAIN);
	ssize_t ret;

	ret = nfs_idmap_get_desc(name, namelen, type, strlen(type), &desc);
	if (ret < 0)
		return ERR_PTR(ret);

	if (!idmap->cred || idmap->cred->user_ns == &init_user_ns)
		rkey = request_key(&key_type_id_resolver, desc, "");
	if (IS_ERR(rkey)) {
		mutex_lock(&idmap->idmap_mutex);
		rkey = request_key_with_auxdata(&key_type_id_resolver_legacy,
						desc, NULL, "", 0, idmap);
		mutex_unlock(&idmap->idmap_mutex);
	}
	if (!IS_ERR(rkey))
		set_bit(KEY_FLAG_ROOT_CAN_INVAL, &rkey->flags);

	kfree(desc);
	return rkey;
}