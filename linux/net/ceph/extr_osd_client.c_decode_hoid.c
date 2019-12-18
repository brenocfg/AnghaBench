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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ceph_hobject_id {int /*<<< orphan*/  pool; int /*<<< orphan*/ * nspace; int /*<<< orphan*/  nspace_len; int /*<<< orphan*/  is_max; int /*<<< orphan*/  hash; int /*<<< orphan*/  snapid; int /*<<< orphan*/ * oid; int /*<<< orphan*/  oid_len; int /*<<< orphan*/ * key; int /*<<< orphan*/  key_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_64_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_8_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ceph_extract_encoded_string (void**,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_hoid_build_hash_cache (struct ceph_hobject_id*) ; 
 int ceph_start_decoding (void**,void*,int,char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_inval ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int decode_hoid(void **p, void *end, struct ceph_hobject_id *hoid)
{
	u8 struct_v;
	u32 struct_len;
	int ret;

	ret = ceph_start_decoding(p, end, 4, "hobject_t", &struct_v,
				  &struct_len);
	if (ret)
		return ret;

	if (struct_v < 4) {
		pr_err("got struct_v %d < 4 of hobject_t\n", struct_v);
		goto e_inval;
	}

	hoid->key = ceph_extract_encoded_string(p, end, &hoid->key_len,
						GFP_NOIO);
	if (IS_ERR(hoid->key)) {
		ret = PTR_ERR(hoid->key);
		hoid->key = NULL;
		return ret;
	}

	hoid->oid = ceph_extract_encoded_string(p, end, &hoid->oid_len,
						GFP_NOIO);
	if (IS_ERR(hoid->oid)) {
		ret = PTR_ERR(hoid->oid);
		hoid->oid = NULL;
		return ret;
	}

	ceph_decode_64_safe(p, end, hoid->snapid, e_inval);
	ceph_decode_32_safe(p, end, hoid->hash, e_inval);
	ceph_decode_8_safe(p, end, hoid->is_max, e_inval);

	hoid->nspace = ceph_extract_encoded_string(p, end, &hoid->nspace_len,
						   GFP_NOIO);
	if (IS_ERR(hoid->nspace)) {
		ret = PTR_ERR(hoid->nspace);
		hoid->nspace = NULL;
		return ret;
	}

	ceph_decode_64_safe(p, end, hoid->pool, e_inval);

	ceph_hoid_build_hash_cache(hoid);
	return 0;

e_inval:
	return -EINVAL;
}