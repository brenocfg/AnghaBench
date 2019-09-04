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
 int /*<<< orphan*/  BIT_DIVIDER_MIPS ; 
 int /*<<< orphan*/  bits_mips ; 
 int /*<<< orphan*/  rubin_do_decompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jffs2_rubinmips_decompress(unsigned char *data_in,
				      unsigned char *cpage_out,
				      uint32_t sourcelen, uint32_t dstlen)
{
	rubin_do_decompress(BIT_DIVIDER_MIPS, bits_mips, data_in,
			    cpage_out, sourcelen, dstlen);
	return 0;
}