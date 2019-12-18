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
struct ceph_crypto_key {int type; } ;

/* Variables and functions */
#define  CEPH_CRYPTO_AES 129 
#define  CEPH_CRYPTO_NONE 128 
 int ENOTSUPP ; 
 int ceph_aes_crypt (struct ceph_crypto_key const*,int,void*,int,int,int*) ; 

int ceph_crypt(const struct ceph_crypto_key *key, bool encrypt,
	       void *buf, int buf_len, int in_len, int *pout_len)
{
	switch (key->type) {
	case CEPH_CRYPTO_NONE:
		*pout_len = in_len;
		return 0;
	case CEPH_CRYPTO_AES:
		return ceph_aes_crypt(key, encrypt, buf, buf_len, in_len,
				      pout_len);
	default:
		return -ENOTSUPP;
	}
}