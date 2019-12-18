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
struct pc1_ctx {int dummy; } ;

/* Variables and functions */
 unsigned char pc1_decrypt (struct pc1_ctx*,unsigned char) ; 

__attribute__((used)) static void pc1_decrypt_buf(struct pc1_ctx *pc1, unsigned char *buf,
			    unsigned len)
{
	unsigned i;

	for (i = 0; i < len; i++)
		buf[i] = pc1_decrypt(pc1, buf[i]);
}