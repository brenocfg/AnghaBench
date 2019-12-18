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
typedef  int ULONGLONG ;
typedef  int ULONG ;
typedef  int UCHAR ;

/* Variables and functions */

void kuhl_m_sr98_em4100_blocks(ULONG blocks[3], ULONGLONG CardNumber)
{
	ULONGLONG tmpData = 0xff80000000000000;
	UCHAR data, i, j, tmp, p, pl[4] = {0};
	for(i = 0; i < 10; i++)
	{
		data = (CardNumber >> (36 - (i * 4))) & 0xf;
		for(p = j = 0; j < 4; j++)
		{
			tmp = (data >> j) & 1;
			p ^= tmp;
			pl[j] ^= tmp;
		}
		tmpData |= (ULONGLONG) data << (51 - (i * 5)) | (ULONGLONG) p << (50 - (i * 5));
	}
	tmpData |= pl[3] << 4 | pl[2] << 3 | pl[1] << 2 | pl[0] << 1;
	blocks[0] = 0x00148040; // RF/64, Manchester, [1-2]
	blocks[1] = (ULONG) (tmpData >> 32);
	blocks[2] = (ULONG) tmpData;
}