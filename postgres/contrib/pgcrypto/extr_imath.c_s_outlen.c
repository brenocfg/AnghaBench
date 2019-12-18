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
typedef  size_t mp_size ;
typedef  scalar_t__ mp_result ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 size_t MP_MAX_RADIX ; 
 size_t MP_MIN_RADIX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mp_int_count_bits (int /*<<< orphan*/ ) ; 
 double* s_log2 ; 

__attribute__((used)) static int
s_outlen(mp_int z, mp_size r)
{
	assert(r >= MP_MIN_RADIX && r <= MP_MAX_RADIX);

	mp_result	bits = mp_int_count_bits(z);
	double		raw = (double) bits * s_log2[r];

	return (int) (raw + 0.999999);
}