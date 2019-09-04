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
typedef  int uint32_t ;
struct bch_control {int* mod8_tab; } ;

/* Variables and functions */
 int BCH_ECC_WORDS (struct bch_control*) ; 

__attribute__((used)) static void encode_bch_unaligned(struct bch_control *bch,
				 const unsigned char *data, unsigned int len,
				 uint32_t *ecc)
{
	int i;
	const uint32_t *p;
	const int l = BCH_ECC_WORDS(bch)-1;

	while (len--) {
		p = bch->mod8_tab + (l+1)*(((ecc[0] >> 24)^(*data++)) & 0xff);

		for (i = 0; i < l; i++)
			ecc[i] = ((ecc[i] << 8)|(ecc[i+1] >> 24))^(*p++);

		ecc[l] = (ecc[l] << 8)^(*p);
	}
}