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

/* Variables and functions */
 int /*<<< orphan*/  MAX_HASH_FUNCS ; 
 int Max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Min (int,int /*<<< orphan*/ ) ; 
 int log (double) ; 
 int rint (int) ; 

__attribute__((used)) static int
optimal_k(uint64 bitset_bits, int64 total_elems)
{
	int			k = rint(log(2.0) * bitset_bits / total_elems);

	return Max(1, Min(k, MAX_HASH_FUNCS));
}