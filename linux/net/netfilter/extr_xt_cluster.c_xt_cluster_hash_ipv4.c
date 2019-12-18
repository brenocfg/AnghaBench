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

/* Variables and functions */
 int /*<<< orphan*/  jhash_1word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u_int32_t
xt_cluster_hash_ipv4(u_int32_t ip, const struct xt_cluster_match_info *info)
{
	return jhash_1word(ip, info->hash_seed);
}