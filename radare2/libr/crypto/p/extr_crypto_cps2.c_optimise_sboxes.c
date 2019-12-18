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
struct sbox {int* table; int* outputs; int /*<<< orphan*/  inputs; } ;
struct optimised_sbox {int* output; int /*<<< orphan*/ * input_lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  extract_inputs (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void optimise_sboxes(struct optimised_sbox* out, const struct sbox* in) {
	int i, box;

	for (box = 0; box < 4; ++box) {
		// precalculate the input lookup
		for (i = 0; i < 256; ++i) {
			out[box].input_lookup[i] = extract_inputs(i, in[box].inputs);
		}
		// precalculate the output masks
		for (i = 0; i < 64; ++i) {
			int o = in[box].table[i];
			out[box].output[i] = 0;
			if (o & 1) {
				out[box].output[i] |= 1 << in[box].outputs[0];
			}
			if (o & 2) {
				out[box].output[i] |= 1 << in[box].outputs[1];
			}
		}
	}
}