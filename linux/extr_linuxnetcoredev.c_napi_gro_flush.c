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
typedef  scalar_t__ u32 ;
struct napi_struct {int /*<<< orphan*/  gro_bitmask; } ;

/* Variables and functions */
 scalar_t__ GRO_HASH_BUCKETS ; 
 int /*<<< orphan*/  __napi_gro_flush_chain (struct napi_struct*,scalar_t__,int) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ *) ; 

void napi_gro_flush(struct napi_struct *napi, bool flush_old)
{
	u32 i;

	for (i = 0; i < GRO_HASH_BUCKETS; i++) {
		if (test_bit(i, &napi->gro_bitmask))
			__napi_gro_flush_chain(napi, i, flush_old);
	}
}