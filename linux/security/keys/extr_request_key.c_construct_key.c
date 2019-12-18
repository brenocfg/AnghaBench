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
struct key {int /*<<< orphan*/  flags; TYPE_1__* type; int /*<<< orphan*/  serial; } ;
typedef  int (* request_key_actor_t ) (struct key*,void*) ;
struct TYPE_2__ {int (* request_key ) (struct key*,void*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_FLAG_INVALIDATED ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int call_sbin_request_key (struct key*,void*) ; 
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,void const*,size_t,void*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  kleave (char*,int) ; 
 struct key* request_key_auth_new (struct key*,char*,void const*,size_t,struct key*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int construct_key(struct key *key, const void *callout_info,
			 size_t callout_len, void *aux,
			 struct key *dest_keyring)
{
	request_key_actor_t actor;
	struct key *authkey;
	int ret;

	kenter("%d,%p,%zu,%p", key->serial, callout_info, callout_len, aux);

	/* allocate an authorisation key */
	authkey = request_key_auth_new(key, "create", callout_info, callout_len,
				       dest_keyring);
	if (IS_ERR(authkey))
		return PTR_ERR(authkey);

	/* Make the call */
	actor = call_sbin_request_key;
	if (key->type->request_key)
		actor = key->type->request_key;

	ret = actor(authkey, aux);

	/* check that the actor called complete_request_key() prior to
	 * returning an error */
	WARN_ON(ret < 0 &&
		!test_bit(KEY_FLAG_INVALIDATED, &authkey->flags));

	key_put(authkey);
	kleave(" = %d", ret);
	return ret;
}