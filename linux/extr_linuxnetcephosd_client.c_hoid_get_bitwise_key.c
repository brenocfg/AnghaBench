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
typedef  int u64 ;
struct ceph_hobject_id {int hash_reverse_bits; scalar_t__ is_max; } ;

/* Variables and functions */

__attribute__((used)) static u64 hoid_get_bitwise_key(const struct ceph_hobject_id *hoid)
{
	return hoid->is_max ? 0x100000000ull : hoid->hash_reverse_bits;
}