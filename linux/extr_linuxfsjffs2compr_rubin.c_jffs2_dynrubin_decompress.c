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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  rubin_do_decompress (int,int*,unsigned char*,unsigned char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int jffs2_dynrubin_decompress(unsigned char *data_in,
				     unsigned char *cpage_out,
				     uint32_t sourcelen, uint32_t dstlen)
{
	int bits[8];
	int c;

	for (c=0; c<8; c++)
		bits[c] = data_in[c];

	rubin_do_decompress(256, bits, data_in+8, cpage_out, sourcelen-8,
			    dstlen);
	return 0;
}