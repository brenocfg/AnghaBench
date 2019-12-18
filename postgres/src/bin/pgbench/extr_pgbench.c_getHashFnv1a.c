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
typedef  int uint64 ;
typedef  int int64 ;
typedef  int int32 ;

/* Variables and functions */
 int FNV_OFFSET_BASIS ; 
 int FNV_PRIME ; 

__attribute__((used)) static int64
getHashFnv1a(int64 val, uint64 seed)
{
	int64		result;
	int			i;

	result = FNV_OFFSET_BASIS ^ seed;
	for (i = 0; i < 8; ++i)
	{
		int32		octet = val & 0xff;

		val = val >> 8;
		result = result ^ octet;
		result = result * FNV_PRIME;
	}

	return result;
}