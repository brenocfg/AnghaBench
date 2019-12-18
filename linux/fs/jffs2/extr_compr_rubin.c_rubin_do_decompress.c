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
struct rubin_state {int /*<<< orphan*/  pp; } ;

/* Variables and functions */
 unsigned char in_byte (struct rubin_state*) ; 
 int /*<<< orphan*/  init_decode (struct rubin_state*,int,int*) ; 
 int /*<<< orphan*/  init_pushpull (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rubin_do_decompress(int bit_divider, int *bits,
				unsigned char *cdata_in, 
				unsigned char *page_out, uint32_t srclen,
				uint32_t destlen)
{
	int outpos = 0;
	struct rubin_state rs;

	init_pushpull(&rs.pp, cdata_in, srclen, 0, 0);
	init_decode(&rs, bit_divider, bits);

	while (outpos < destlen)
		page_out[outpos++] = in_byte(&rs);
}