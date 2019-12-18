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
struct ceph_hobject_id {scalar_t__ is_max; scalar_t__ pool; void* nspace; size_t nspace_len; void* oid; size_t oid_len; scalar_t__ snapid; } ;

/* Variables and functions */
 int compare_names (void*,size_t,void*,size_t) ; 
 scalar_t__ hoid_get_bitwise_key (struct ceph_hobject_id const*) ; 
 int /*<<< orphan*/  hoid_get_effective_key (struct ceph_hobject_id const*,void**,size_t*) ; 

__attribute__((used)) static int hoid_compare(const struct ceph_hobject_id *lhs,
			const struct ceph_hobject_id *rhs)
{
	void *effective_key1, *effective_key2;
	size_t effective_key1_len, effective_key2_len;
	int ret;

	if (lhs->is_max < rhs->is_max)
		return -1;
	if (lhs->is_max > rhs->is_max)
		return 1;

	if (lhs->pool < rhs->pool)
		return -1;
	if (lhs->pool > rhs->pool)
		return 1;

	if (hoid_get_bitwise_key(lhs) < hoid_get_bitwise_key(rhs))
		return -1;
	if (hoid_get_bitwise_key(lhs) > hoid_get_bitwise_key(rhs))
		return 1;

	ret = compare_names(lhs->nspace, lhs->nspace_len,
			    rhs->nspace, rhs->nspace_len);
	if (ret)
		return ret;

	hoid_get_effective_key(lhs, &effective_key1, &effective_key1_len);
	hoid_get_effective_key(rhs, &effective_key2, &effective_key2_len);
	ret = compare_names(effective_key1, effective_key1_len,
			    effective_key2, effective_key2_len);
	if (ret)
		return ret;

	ret = compare_names(lhs->oid, lhs->oid_len, rhs->oid, rhs->oid_len);
	if (ret)
		return ret;

	if (lhs->snapid < rhs->snapid)
		return -1;
	if (lhs->snapid > rhs->snapid)
		return 1;

	return 0;
}