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
typedef  int uint32 ;
typedef  int pg_int64 ;

/* Variables and functions */
 scalar_t__ pg_ntoh32 (int) ; 

__attribute__((used)) static pg_int64
lo_ntoh64(pg_int64 net64)
{
	union
	{
		pg_int64	i64;
		uint32		i32[2];
	}			swap;
	pg_int64	result;

	swap.i64 = net64;

	result = (uint32) pg_ntoh32(swap.i32[0]);
	result <<= 32;
	result |= (uint32) pg_ntoh32(swap.i32[1]);

	return result;
}