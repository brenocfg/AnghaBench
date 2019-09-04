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
struct ceph_hobject_id {int /*<<< orphan*/  pool; int /*<<< orphan*/  nspace_len; int /*<<< orphan*/  nspace; int /*<<< orphan*/  is_max; int /*<<< orphan*/  hash; int /*<<< orphan*/  snapid; int /*<<< orphan*/  oid_len; int /*<<< orphan*/  oid; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_encode_32 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_64 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_8 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_string (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_start_encoding (void**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hoid_encoding_size (struct ceph_hobject_id const*) ; 

__attribute__((used)) static void encode_hoid(void **p, void *end, const struct ceph_hobject_id *hoid)
{
	ceph_start_encoding(p, 4, 3, hoid_encoding_size(hoid));
	ceph_encode_string(p, end, hoid->key, hoid->key_len);
	ceph_encode_string(p, end, hoid->oid, hoid->oid_len);
	ceph_encode_64(p, hoid->snapid);
	ceph_encode_32(p, hoid->hash);
	ceph_encode_8(p, hoid->is_max);
	ceph_encode_string(p, end, hoid->nspace, hoid->nspace_len);
	ceph_encode_64(p, hoid->pool);
}