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

/* Variables and functions */
 int BIT (int const,int const) ; 

__attribute__((used)) static void expand_1st_key(ut32 *dstkey, const ut32 *srckey) {
	static const int bits[96] = {
		33, 58, 49, 36,  0, 31,
		22, 30,  3, 16,  5, 53,
		10, 41, 23, 19, 27, 39,
		43,  6, 34, 12, 61, 21,
		48, 13, 32, 35,  6, 42,
		43, 14, 21, 41, 52, 25,
		18, 47, 46, 37, 57, 53,
		20,  8, 55, 54, 59, 60,
		27, 33, 35, 18,  8, 15,
		63,  1, 50, 44, 16, 46,
		5,  4, 45, 51, 38, 25,
		13, 11, 62, 29, 48,  2,
		59, 61, 62, 56, 51, 57,
		54,  9, 24, 63, 22,  7,
		26, 42, 45, 40, 23, 14,
		2, 31, 52, 28, 44, 17,
	};
	int i;

	dstkey[0] = 0;
	dstkey[1] = 0;
	dstkey[2] = 0;
	dstkey[3] = 0;

	for (i = 0; i < 96; ++i) {
		dstkey[i / 24] |= BIT (srckey[bits[i] / 32], bits[i] % 32) << (i % 24);
	}
}