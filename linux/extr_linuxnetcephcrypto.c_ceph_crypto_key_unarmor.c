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
struct ceph_crypto_key {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int ceph_crypto_key_decode (struct ceph_crypto_key*,void**,void*) ; 
 int ceph_unarmor (void*,char const*,char const*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

int ceph_crypto_key_unarmor(struct ceph_crypto_key *key, const char *inkey)
{
	int inlen = strlen(inkey);
	int blen = inlen * 3 / 4;
	void *buf, *p;
	int ret;

	dout("crypto_key_unarmor %s\n", inkey);
	buf = kmalloc(blen, GFP_NOFS);
	if (!buf)
		return -ENOMEM;
	blen = ceph_unarmor(buf, inkey, inkey+inlen);
	if (blen < 0) {
		kfree(buf);
		return blen;
	}

	p = buf;
	ret = ceph_crypto_key_decode(key, &p, p + blen);
	kfree(buf);
	if (ret)
		return ret;
	dout("crypto_key_unarmor key %p type %d len %d\n", key,
	     key->type, key->len);
	return 0;
}