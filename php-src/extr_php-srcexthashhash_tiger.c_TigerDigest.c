#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* state; } ;
typedef  TYPE_1__ PHP_TIGER_CTX ;

/* Variables and functions */

__attribute__((used)) static inline void TigerDigest(unsigned char *digest_str, unsigned int digest_len, PHP_TIGER_CTX *context)
{
	unsigned int i;

	for (i = 0; i < digest_len; ++i) {
		digest_str[i] = (unsigned char) ((context->state[i/8] >> (8 * (i%8))) & 0xff);
	}
}