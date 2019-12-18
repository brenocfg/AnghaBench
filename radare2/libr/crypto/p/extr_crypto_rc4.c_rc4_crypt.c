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
typedef  size_t ut8 ;
struct rc4_state {size_t index1; size_t index2; size_t* perm; } ;

/* Variables and functions */
 int /*<<< orphan*/  swap_bytes (size_t*,size_t*) ; 

__attribute__((used)) static void rc4_crypt(struct rc4_state *const state, const ut8 *inbuf, ut8 *outbuf, int buflen) {
	int i;
	ut8 j;

	for (i = 0; i < buflen; i++) {
		/* Update modification indices */
		state->index1++;
		state->index2 += state->perm[state->index1];
		/* Modify permutation */
		swap_bytes (&state->perm[state->index1],
		    &state->perm[state->index2]);
		/* Encrypt/decrypt next byte */
		j = state->perm[state->index1] + state->perm[state->index2];
		outbuf[i] = inbuf[i] ^ state->perm[j];
	}
}