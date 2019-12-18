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
typedef  int ut32 ;
typedef  int /*<<< orphan*/  ut16 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void expand_subkey(ut32* subkey, ut16 seed) {
	// Note that each row of the table is a permutation of the seed bits.
	static const int bits[64] = {
		5, 10, 14,  9,  4,  0, 15,  6,  1,  8,  3,  2, 12,  7, 13, 11,
		5, 12,  7,  2, 13, 11,  9, 14,  4,  1,  6, 10,  8,  0, 15,  3,
		4, 10,  2,  0,  6,  9, 12,  1, 11,  7, 15,  8, 13,  5, 14,  3,
		14, 11, 12,  7,  4,  5,  2, 10,  1, 15,  0,  9,  8,  6, 13,  3,
	};
	int i;

	subkey[0] = 0;
	subkey[1] = 0;

	for (i = 0; i < 64; ++i) {
		subkey[i / 32] |= BIT(seed, bits[i]) << (i % 32);
	}
}