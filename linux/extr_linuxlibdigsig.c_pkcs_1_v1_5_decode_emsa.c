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

__attribute__((used)) static const char *pkcs_1_v1_5_decode_emsa(const unsigned char *msg,
						unsigned long  msglen,
						unsigned long  modulus_bitlen,
						unsigned long *outlen)
{
	unsigned long modulus_len, ps_len, i;

	modulus_len = (modulus_bitlen >> 3) + (modulus_bitlen & 7 ? 1 : 0);

	/* test message size */
	if ((msglen > modulus_len) || (modulus_len < 11))
		return NULL;

	/* separate encoded message */
	if (msg[0] != 0x00 || msg[1] != 0x01)
		return NULL;

	for (i = 2; i < modulus_len - 1; i++)
		if (msg[i] != 0xFF)
			break;

	/* separator check */
	if (msg[i] != 0)
		/* There was no octet with hexadecimal value 0x00
		to separate ps from m. */
		return NULL;

	ps_len = i - 2;

	*outlen = (msglen - (2 + ps_len + 1));

	return msg + 2 + ps_len + 1;
}