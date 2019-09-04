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
typedef  size_t ut32 ;

/* Variables and functions */
 size_t S_ARRAY_SIZE (size_t*) ; 
 size_t UT32_MAX ; 
 size_t* ht_primes_sizes ; 

__attribute__((used)) static inline ut32 compute_size(ut32 idx, ut32 sz) {
	// when possible, use the precomputed prime numbers which help with
	// collisions, otherwise, at least make the number odd with |1
	return idx != UT32_MAX && idx < S_ARRAY_SIZE(ht_primes_sizes) ? ht_primes_sizes[idx] : (sz | 1);
}