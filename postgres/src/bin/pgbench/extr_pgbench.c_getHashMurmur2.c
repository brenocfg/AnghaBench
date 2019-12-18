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
typedef  int /*<<< orphan*/  int64 ;

/* Variables and functions */
 int MM2_MUL ; 
 int MM2_MUL_TIMES_8 ; 
 int MM2_ROT ; 

__attribute__((used)) static int64
getHashMurmur2(int64 val, uint64 seed)
{
	uint64		result = seed ^ MM2_MUL_TIMES_8;	/* sizeof(int64) */
	uint64		k = (uint64) val;

	k *= MM2_MUL;
	k ^= k >> MM2_ROT;
	k *= MM2_MUL;

	result ^= k;
	result *= MM2_MUL;

	result ^= result >> MM2_ROT;
	result *= MM2_MUL;
	result ^= result >> MM2_ROT;

	return (int64) result;
}