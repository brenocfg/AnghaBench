#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_key_auth {TYPE_2__* target_key; } ;
struct TYPE_3__ {struct request_key_auth** data; } ;
struct key {TYPE_1__ payload; } ;
struct iov_iter {int dummy; } ;
struct cred {struct key* request_key_auth; } ;
typedef  scalar_t__ key_serial_t ;
struct TYPE_4__ {scalar_t__ serial; } ;

/* Variables and functions */
 long EFAULT ; 
 long EINVAL ; 
 long ENOMEM ; 
 long EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  copy_from_iter_full (void*,size_t,struct iov_iter*) ; 
 struct cred* current_cred () ; 
 long get_instantiation_keyring (scalar_t__,struct request_key_auth*,struct key**) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kenter (char*,scalar_t__,size_t,scalar_t__) ; 
 long key_instantiate_and_link (TYPE_2__*,void*,size_t,struct key*,struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  keyctl_change_reqkey_auth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero_explicit (void*,size_t) ; 

long keyctl_instantiate_key_common(key_serial_t id,
				   struct iov_iter *from,
				   key_serial_t ringid)
{
	const struct cred *cred = current_cred();
	struct request_key_auth *rka;
	struct key *instkey, *dest_keyring;
	size_t plen = from ? iov_iter_count(from) : 0;
	void *payload;
	long ret;

	kenter("%d,,%zu,%d", id, plen, ringid);

	if (!plen)
		from = NULL;

	ret = -EINVAL;
	if (plen > 1024 * 1024 - 1)
		goto error;

	/* the appropriate instantiation authorisation key must have been
	 * assumed before calling this */
	ret = -EPERM;
	instkey = cred->request_key_auth;
	if (!instkey)
		goto error;

	rka = instkey->payload.data[0];
	if (rka->target_key->serial != id)
		goto error;

	/* pull the payload in if one was supplied */
	payload = NULL;

	if (from) {
		ret = -ENOMEM;
		payload = kvmalloc(plen, GFP_KERNEL);
		if (!payload)
			goto error;

		ret = -EFAULT;
		if (!copy_from_iter_full(payload, plen, from))
			goto error2;
	}

	/* find the destination keyring amongst those belonging to the
	 * requesting task */
	ret = get_instantiation_keyring(ringid, rka, &dest_keyring);
	if (ret < 0)
		goto error2;

	/* instantiate the key and link it into a keyring */
	ret = key_instantiate_and_link(rka->target_key, payload, plen,
				       dest_keyring, instkey);

	key_put(dest_keyring);

	/* discard the assumed authority if it's just been disabled by
	 * instantiation of the key */
	if (ret == 0)
		keyctl_change_reqkey_auth(NULL);

error2:
	if (payload) {
		memzero_explicit(payload, plen);
		kvfree(payload);
	}
error:
	return ret;
}