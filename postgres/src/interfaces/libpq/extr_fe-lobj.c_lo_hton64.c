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
typedef  void* uint32 ;
typedef  int pg_int64 ;

/* Variables and functions */
 void* pg_hton32 (void*) ; 

__attribute__((used)) static pg_int64
lo_hton64(pg_int64 host64)
{
	union
	{
		pg_int64	i64;
		uint32		i32[2];
	}			swap;
	uint32		t;

	/* High order half first, since we're doing MSB-first */
	t = (uint32) (host64 >> 32);
	swap.i32[0] = pg_hton32(t);

	/* Now the low order half */
	t = (uint32) host64;
	swap.i32[1] = pg_hton32(t);

	return swap.i64;
}