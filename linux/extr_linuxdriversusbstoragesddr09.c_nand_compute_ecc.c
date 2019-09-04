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

/* Variables and functions */
 unsigned char* ecc2 ; 
 char* parity ; 

__attribute__((used)) static void nand_compute_ecc(unsigned char *data, unsigned char *ecc) {
	int i, j, a;
	unsigned char par = 0, bit, bits[8] = {0};

	/* collect 16 checksum bits */
	for (i = 0; i < 256; i++) {
		par ^= data[i];
		bit = parity[data[i]];
		for (j = 0; j < 8; j++)
			if ((i & (1<<j)) == 0)
				bits[j] ^= bit;
	}

	/* put 4+4+4 = 12 bits in the ecc */
	a = (bits[3] << 6) + (bits[2] << 4) + (bits[1] << 2) + bits[0];
	ecc[0] = ~(a ^ (a<<1) ^ (parity[par] ? 0xaa : 0));

	a = (bits[7] << 6) + (bits[6] << 4) + (bits[5] << 2) + bits[4];
	ecc[1] = ~(a ^ (a<<1) ^ (parity[par] ? 0xaa : 0));

	ecc[2] = ecc2[par];
}