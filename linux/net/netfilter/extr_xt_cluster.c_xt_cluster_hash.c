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
typedef  int /*<<< orphan*/  u_int32_t ;
struct xt_cluster_match_info {int /*<<< orphan*/  total_nodes; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int nf_ct_l3num (struct nf_conn const*) ; 
 int /*<<< orphan*/  nf_ct_orig_ipv4_src (struct nf_conn const*) ; 
 int /*<<< orphan*/  nf_ct_orig_ipv6_src (struct nf_conn const*) ; 
 int /*<<< orphan*/  reciprocal_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_cluster_hash_ipv4 (int /*<<< orphan*/ ,struct xt_cluster_match_info const*) ; 
 int /*<<< orphan*/  xt_cluster_hash_ipv6 (int /*<<< orphan*/ ,struct xt_cluster_match_info const*) ; 

__attribute__((used)) static inline u_int32_t
xt_cluster_hash(const struct nf_conn *ct,
		const struct xt_cluster_match_info *info)
{
	u_int32_t hash = 0;

	switch(nf_ct_l3num(ct)) {
	case AF_INET:
		hash = xt_cluster_hash_ipv4(nf_ct_orig_ipv4_src(ct), info);
		break;
	case AF_INET6:
		hash = xt_cluster_hash_ipv6(nf_ct_orig_ipv6_src(ct), info);
		break;
	default:
		WARN_ON(1);
		break;
	}

	return reciprocal_scale(hash, info->total_nodes);
}