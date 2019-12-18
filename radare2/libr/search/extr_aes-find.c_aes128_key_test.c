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
 unsigned char const* table_sbox ; 

__attribute__((used)) static bool aes128_key_test(const unsigned char *buf) {
	return (buf[16] == (buf[0] ^ table_sbox[buf[13]] ^ 1) \
		&& buf[17] == (buf[1] ^ table_sbox[buf[14]]) \
		&& buf[18] == (buf[2] ^ table_sbox[buf[15]]) \
		&& buf[19] == (buf[3] ^ table_sbox[buf[12]]));
}