#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct xt_hashlimit_htable {TYPE_1__ cfg; int /*<<< orphan*/  rnd; } ;
struct dsthash_dst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash2 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reciprocal_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
hash_dst(const struct xt_hashlimit_htable *ht, const struct dsthash_dst *dst)
{
	u_int32_t hash = jhash2((const u32 *)dst,
				sizeof(*dst)/sizeof(u32),
				ht->rnd);
	/*
	 * Instead of returning hash % ht->cfg.size (implying a divide)
	 * we return the high 32 bits of the (hash * ht->cfg.size) that will
	 * give results between [0 and cfg.size-1] and same hash distribution,
	 * but using a multiply, less expensive than a divide
	 */
	return reciprocal_scale(hash, ht->cfg.size);
}