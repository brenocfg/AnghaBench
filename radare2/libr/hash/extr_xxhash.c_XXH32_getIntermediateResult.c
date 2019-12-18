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
typedef  int ut8 ;
typedef  int ut32 ;
struct XXH_state32_t {int memsize; int total_len; int v1; int v2; int v3; int v4; int seed; scalar_t__ memory; } ;

/* Variables and functions */
 int PRIME32_1 ; 
 int PRIME32_2 ; 
 int PRIME32_3 ; 
 int PRIME32_4 ; 
 int PRIME32_5 ; 
 int XXH_rotl32 (int,int) ; 
 int r_read_le32 (int*) ; 

ut32 XXH32_getIntermediateResult (void *state_in) {
	struct XXH_state32_t *state = state_in;
	ut8 *p = (ut8 *) state->memory;
	ut8 *bEnd = (ut8 *) state->memory + state->memsize;
	ut32 h32;

	if (state->total_len >= 16) {
		h32 = XXH_rotl32 (state->v1, 1) + XXH_rotl32 (state->v2, 7) +
		XXH_rotl32 (state->v3, 12) + XXH_rotl32 (state->v4, 18);
	} else {
		h32 = state->seed + PRIME32_5;
	}

	h32 += (ut32) state->total_len;

	while (p <= bEnd - 4) {
		h32 += r_read_le32 (p) * PRIME32_3;
		h32 = XXH_rotl32 (h32, 17) * PRIME32_4;
		p += 4;
	}
	while (p < bEnd) {
		h32 += (*p) * PRIME32_5;
		h32 = XXH_rotl32 (h32, 11) * PRIME32_1;
		p++;
	}
	h32 ^= h32 >> 15;
	h32 *= PRIME32_2;
	h32 ^= h32 >> 13;
	h32 *= PRIME32_3;
	h32 ^= h32 >> 16;
	return h32;
}