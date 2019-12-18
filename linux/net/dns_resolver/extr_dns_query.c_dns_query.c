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
typedef  int /*<<< orphan*/  time64_t ;
struct user_key_payload {int datalen; int /*<<< orphan*/  data; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct key** data; } ;
struct key {int /*<<< orphan*/  sem; int /*<<< orphan*/  expiry; TYPE_1__ payload; int /*<<< orphan*/  perm; int /*<<< orphan*/  flags; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_FLAG_ROOT_CAN_INVAL ; 
 int /*<<< orphan*/  KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 size_t dns_key_error ; 
 int /*<<< orphan*/  dns_resolver_cache ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kdebug (char*,char*,char const*) ; 
 int /*<<< orphan*/  kenter (char*,char const*,int,int,char const*,size_t,char const*) ; 
 int /*<<< orphan*/  key_invalidate (struct key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_dns_resolver ; 
 int key_validate (struct key*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kleave (char*,int) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 char* kmemdup_nul (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 struct cred* override_creds (int /*<<< orphan*/ ) ; 
 struct key* request_key_net (int /*<<< orphan*/ *,char*,struct net*,char const*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct user_key_payload* user_key_payload_locked (struct key*) ; 

int dns_query(struct net *net,
	      const char *type, const char *name, size_t namelen,
	      const char *options, char **_result, time64_t *_expiry,
	      bool invalidate)
{
	struct key *rkey;
	struct user_key_payload *upayload;
	const struct cred *saved_cred;
	size_t typelen, desclen;
	char *desc, *cp;
	int ret, len;

	kenter("%s,%*.*s,%zu,%s",
	       type, (int)namelen, (int)namelen, name, namelen, options);

	if (!name || namelen == 0)
		return -EINVAL;

	/* construct the query key description as "[<type>:]<name>" */
	typelen = 0;
	desclen = 0;
	if (type) {
		typelen = strlen(type);
		if (typelen < 1)
			return -EINVAL;
		desclen += typelen + 1;
	}

	if (namelen < 3 || namelen > 255)
		return -EINVAL;
	desclen += namelen + 1;

	desc = kmalloc(desclen, GFP_KERNEL);
	if (!desc)
		return -ENOMEM;

	cp = desc;
	if (type) {
		memcpy(cp, type, typelen);
		cp += typelen;
		*cp++ = ':';
	}
	memcpy(cp, name, namelen);
	cp += namelen;
	*cp = '\0';

	if (!options)
		options = "";
	kdebug("call request_key(,%s,%s)", desc, options);

	/* make the upcall, using special credentials to prevent the use of
	 * add_key() to preinstall malicious redirections
	 */
	saved_cred = override_creds(dns_resolver_cache);
	rkey = request_key_net(&key_type_dns_resolver, desc, net, options);
	revert_creds(saved_cred);
	kfree(desc);
	if (IS_ERR(rkey)) {
		ret = PTR_ERR(rkey);
		goto out;
	}

	down_read(&rkey->sem);
	set_bit(KEY_FLAG_ROOT_CAN_INVAL, &rkey->flags);
	rkey->perm |= KEY_USR_VIEW;

	ret = key_validate(rkey);
	if (ret < 0)
		goto put;

	/* If the DNS server gave an error, return that to the caller */
	ret = PTR_ERR(rkey->payload.data[dns_key_error]);
	if (ret)
		goto put;

	upayload = user_key_payload_locked(rkey);
	len = upayload->datalen;

	if (_result) {
		ret = -ENOMEM;
		*_result = kmemdup_nul(upayload->data, len, GFP_KERNEL);
		if (!*_result)
			goto put;
	}

	if (_expiry)
		*_expiry = rkey->expiry;

	ret = len;
put:
	up_read(&rkey->sem);
	if (invalidate)
		key_invalidate(rkey);
	key_put(rkey);
out:
	kleave(" = %d", ret);
	return ret;
}