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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sw_flow_key_range {int start; int end; } ;
struct sw_flow_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  jhash2 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 flow_hash(const struct sw_flow_key *key,
		     const struct sw_flow_key_range *range)
{
	int key_start = range->start;
	int key_end = range->end;
	const u32 *hash_key = (const u32 *)((const u8 *)key + key_start);
	int hash_u32s = (key_end - key_start) >> 2;

	/* Make sure number of hash bytes are multiple of u32. */
	BUILD_BUG_ON(sizeof(long) % sizeof(u32));

	return jhash2(hash_key, hash_u32s, 0);
}