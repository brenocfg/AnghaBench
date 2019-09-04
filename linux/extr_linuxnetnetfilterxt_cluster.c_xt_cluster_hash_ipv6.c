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
struct xt_cluster_match_info {int /*<<< orphan*/  hash_seed; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int NF_CT_TUPLE_L3SIZE ; 
 int /*<<< orphan*/  jhash2 (void const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u_int32_t
xt_cluster_hash_ipv6(const void *ip, const struct xt_cluster_match_info *info)
{
	return jhash2(ip, NF_CT_TUPLE_L3SIZE / sizeof(__u32), info->hash_seed);
}