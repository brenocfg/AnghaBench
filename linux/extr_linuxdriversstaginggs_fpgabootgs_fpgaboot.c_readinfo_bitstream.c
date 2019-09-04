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
typedef  char u8 ;
typedef  int u16 ;

/* Variables and functions */
 int EINVAL ; 
 int get_unaligned_be16 (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  read_bitstream (char*,char*,int*,int) ; 

__attribute__((used)) static int readinfo_bitstream(u8 *bitdata, u8 *buf, int size, int *offset)
{
	u8 tbuf[2];
	u16 len;

	/* read section char */
	read_bitstream(bitdata, tbuf, offset, 1);

	/* read length */
	read_bitstream(bitdata, tbuf, offset, 2);

	len = get_unaligned_be16(tbuf);
	if (len >= size) {
		pr_err("error: readinfo buffer too small\n");
		return -EINVAL;
	}

	read_bitstream(bitdata, buf, offset, len);
	buf[len] = '\0';

	return 0;
}