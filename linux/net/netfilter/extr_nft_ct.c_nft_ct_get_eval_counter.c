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
typedef  scalar_t__ u64 ;
struct nf_conn_counter {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
typedef  enum nft_ct_keys { ____Placeholder_nft_ct_keys } nft_ct_keys ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;

/* Variables and functions */
 int IP_CT_DIR_MAX ; 
 int IP_CT_DIR_ORIGINAL ; 
 int IP_CT_DIR_REPLY ; 
 int NFT_CT_BYTES ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 nft_ct_get_eval_counter(const struct nf_conn_counter *c,
				   enum nft_ct_keys k,
				   enum ip_conntrack_dir d)
{
	if (d < IP_CT_DIR_MAX)
		return k == NFT_CT_BYTES ? atomic64_read(&c[d].bytes) :
					   atomic64_read(&c[d].packets);

	return nft_ct_get_eval_counter(c, k, IP_CT_DIR_ORIGINAL) +
	       nft_ct_get_eval_counter(c, k, IP_CT_DIR_REPLY);
}