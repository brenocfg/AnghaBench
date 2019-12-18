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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct bch_control {int dummy; } ;

/* Variables and functions */
 scalar_t__ BCH_ECC_BYTES (struct bch_control*) ; 
 int BCH_ECC_WORDS (struct bch_control*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 

__attribute__((used)) static void store_ecc8(struct bch_control *bch, uint8_t *dst,
		       const uint32_t *src)
{
	uint8_t pad[4];
	unsigned int i, nwords = BCH_ECC_WORDS(bch)-1;

	for (i = 0; i < nwords; i++) {
		*dst++ = (src[i] >> 24);
		*dst++ = (src[i] >> 16) & 0xff;
		*dst++ = (src[i] >>  8) & 0xff;
		*dst++ = (src[i] >>  0) & 0xff;
	}
	pad[0] = (src[nwords] >> 24);
	pad[1] = (src[nwords] >> 16) & 0xff;
	pad[2] = (src[nwords] >>  8) & 0xff;
	pad[3] = (src[nwords] >>  0) & 0xff;
	memcpy(dst, pad, BCH_ECC_BYTES(bch)-4*nwords);
}