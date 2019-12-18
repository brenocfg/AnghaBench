#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_key_auth {size_t callout_len; void* dest_keyring; void* target_key; int /*<<< orphan*/  pid; struct cred const* cred; int /*<<< orphan*/  op; int /*<<< orphan*/  callout_info; } ;
struct key {int serial; int /*<<< orphan*/  usage; } ;
struct cred {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; TYPE_2__* request_key_auth; } ;
struct TYPE_6__ {int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {struct request_key_auth** data; } ;
struct TYPE_5__ {int /*<<< orphan*/  sem; TYPE_1__ payload; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EKEYREVOKED ; 
 int ENOMEM ; 
 struct key* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_NOT_IN_QUOTA ; 
 int /*<<< orphan*/  KEY_FLAG_REVOKED ; 
 int KEY_POS_LINK ; 
 int KEY_POS_READ ; 
 int KEY_POS_SEARCH ; 
 int KEY_POS_VIEW ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 TYPE_3__* current ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_request_key_auth (struct request_key_auth*) ; 
 void* get_cred (struct cred const*) ; 
 int /*<<< orphan*/  kenter (char*,int) ; 
 struct key* key_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* key_get (struct key*) ; 
 int key_instantiate_and_link (struct key*,struct request_key_auth*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_request_key_auth ; 
 int /*<<< orphan*/  kleave (char*,int,...) ; 
 int /*<<< orphan*/  kmemdup (void const*,size_t,int /*<<< orphan*/ ) ; 
 struct request_key_auth* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct key *request_key_auth_new(struct key *target, const char *op,
				 const void *callout_info, size_t callout_len,
				 struct key *dest_keyring)
{
	struct request_key_auth *rka, *irka;
	const struct cred *cred = current_cred();
	struct key *authkey = NULL;
	char desc[20];
	int ret = -ENOMEM;

	kenter("%d,", target->serial);

	/* allocate a auth record */
	rka = kzalloc(sizeof(*rka), GFP_KERNEL);
	if (!rka)
		goto error;
	rka->callout_info = kmemdup(callout_info, callout_len, GFP_KERNEL);
	if (!rka->callout_info)
		goto error_free_rka;
	rka->callout_len = callout_len;
	strlcpy(rka->op, op, sizeof(rka->op));

	/* see if the calling process is already servicing the key request of
	 * another process */
	if (cred->request_key_auth) {
		/* it is - use that instantiation context here too */
		down_read(&cred->request_key_auth->sem);

		/* if the auth key has been revoked, then the key we're
		 * servicing is already instantiated */
		if (test_bit(KEY_FLAG_REVOKED,
			     &cred->request_key_auth->flags)) {
			up_read(&cred->request_key_auth->sem);
			ret = -EKEYREVOKED;
			goto error_free_rka;
		}

		irka = cred->request_key_auth->payload.data[0];
		rka->cred = get_cred(irka->cred);
		rka->pid = irka->pid;

		up_read(&cred->request_key_auth->sem);
	}
	else {
		/* it isn't - use this process as the context */
		rka->cred = get_cred(cred);
		rka->pid = current->pid;
	}

	rka->target_key = key_get(target);
	rka->dest_keyring = key_get(dest_keyring);

	/* allocate the auth key */
	sprintf(desc, "%x", target->serial);

	authkey = key_alloc(&key_type_request_key_auth, desc,
			    cred->fsuid, cred->fsgid, cred,
			    KEY_POS_VIEW | KEY_POS_READ | KEY_POS_SEARCH | KEY_POS_LINK |
			    KEY_USR_VIEW, KEY_ALLOC_NOT_IN_QUOTA, NULL);
	if (IS_ERR(authkey)) {
		ret = PTR_ERR(authkey);
		goto error_free_rka;
	}

	/* construct the auth key */
	ret = key_instantiate_and_link(authkey, rka, 0, NULL, NULL);
	if (ret < 0)
		goto error_put_authkey;

	kleave(" = {%d,%d}", authkey->serial, refcount_read(&authkey->usage));
	return authkey;

error_put_authkey:
	key_put(authkey);
error_free_rka:
	free_request_key_auth(rka);
error:
	kleave("= %d", ret);
	return ERR_PTR(ret);
}