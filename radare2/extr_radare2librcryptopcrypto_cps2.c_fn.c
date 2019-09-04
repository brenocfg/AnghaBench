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
typedef  int ut32 ;
struct optimised_sbox {size_t* output; int* input_lookup; } ;

/* Variables and functions */

__attribute__((used)) static ut8 fn(ut8 in, const struct optimised_sbox *sboxes, ut32 key) {
	const struct optimised_sbox *sbox1 = &sboxes[0];
	const struct optimised_sbox *sbox2 = &sboxes[1];
	const struct optimised_sbox *sbox3 = &sboxes[2];
	const struct optimised_sbox *sbox4 = &sboxes[3];

	return
		sbox1->output[sbox1->input_lookup[in] ^ ((key >>  0) & 0x3f)] |
		sbox2->output[sbox2->input_lookup[in] ^ ((key >>  6) & 0x3f)] |
		sbox3->output[sbox3->input_lookup[in] ^ ((key >> 12) & 0x3f)] |
		sbox4->output[sbox4->input_lookup[in] ^ ((key >> 18) & 0x3f)];
}