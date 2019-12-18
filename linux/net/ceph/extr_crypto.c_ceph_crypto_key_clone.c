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
struct ceph_crypto_key {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct ceph_crypto_key*,struct ceph_crypto_key const*,int) ; 
 int set_secret (struct ceph_crypto_key*,int /*<<< orphan*/ ) ; 

int ceph_crypto_key_clone(struct ceph_crypto_key *dst,
			  const struct ceph_crypto_key *src)
{
	memcpy(dst, src, sizeof(struct ceph_crypto_key));
	return set_secret(dst, src->key);
}