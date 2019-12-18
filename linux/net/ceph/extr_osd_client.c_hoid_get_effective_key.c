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
struct ceph_hobject_id {size_t key_len; size_t oid_len; void* oid; void* key; } ;

/* Variables and functions */

__attribute__((used)) static void hoid_get_effective_key(const struct ceph_hobject_id *hoid,
				   void **pkey, size_t *pkey_len)
{
	if (hoid->key_len) {
		*pkey = hoid->key;
		*pkey_len = hoid->key_len;
	} else {
		*pkey = hoid->oid;
		*pkey_len = hoid->oid_len;
	}
}