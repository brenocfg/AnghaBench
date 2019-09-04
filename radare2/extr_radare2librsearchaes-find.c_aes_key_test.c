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

__attribute__((used)) static int aes_key_test(const unsigned char *buf) {
	return (buf[28]==table_sbox[buf[15]] \
	    &&  buf[29]==table_sbox[buf[12]] \
	    &&  buf[30]==table_sbox[buf[13]] \
	    &&  buf[31]==(table_sbox[buf[14]]^1))?1:0;
}