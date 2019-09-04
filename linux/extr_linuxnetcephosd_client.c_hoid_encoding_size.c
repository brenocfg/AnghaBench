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
struct ceph_hobject_id {int key_len; int oid_len; int nspace_len; } ;

/* Variables and functions */

__attribute__((used)) static int hoid_encoding_size(const struct ceph_hobject_id *hoid)
{
	return 8 + 4 + 1 + 8 + /* snapid, hash, is_max, pool */
	       4 + hoid->key_len + 4 + hoid->oid_len + 4 + hoid->nspace_len;
}