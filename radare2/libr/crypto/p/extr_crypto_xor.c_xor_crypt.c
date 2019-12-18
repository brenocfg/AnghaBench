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
struct xor_state {int const* key; int key_size; } ;

/* Variables and functions */

__attribute__((used)) static void xor_crypt(struct xor_state *const state, const ut8 *inbuf, ut8 *outbuf, int buflen) {
	int i;//index for input
	for (i = 0; i < buflen; i++) {
		outbuf[i] = inbuf[i] ^ state->key[(i%state->key_size)];
	}
}