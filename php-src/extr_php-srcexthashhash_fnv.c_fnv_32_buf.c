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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_FNV_32_PRIME ; 

__attribute__((used)) static uint32_t
fnv_32_buf(void *buf, size_t len, uint32_t hval, int alternate)
{
	unsigned char *bp = (unsigned char *)buf;   /* start of buffer */
	unsigned char *be = bp + len;	   /* beyond end of buffer */

	/*
	 * FNV-1 hash each octet in the buffer
	 */
	if (alternate == 0) {
		while (bp < be) {
			/* multiply by the 32 bit FNV magic prime mod 2^32 */
			hval *= PHP_FNV_32_PRIME;

			/* xor the bottom with the current octet */
			hval ^= (uint32_t)*bp++;
		}
	} else {
		while (bp < be) {
			/* xor the bottom with the current octet */
			hval ^= (uint32_t)*bp++;

			/* multiply by the 32 bit FNV magic prime mod 2^32 */
			hval *= PHP_FNV_32_PRIME;
		}
	}

	/* return our new hash value */
	return hval;
}