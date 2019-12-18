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
typedef  size_t uint8 ;
typedef  int uint32 ;
typedef  int pg_crc32c ;

/* Variables and functions */
 int CRC8 (int /*<<< orphan*/ ) ; 
 int** pg_crc32c_table ; 

pg_crc32c
pg_comp_crc32c_sb8(pg_crc32c crc, const void *data, size_t len)
{
	const unsigned char *p = data;
	const uint32 *p4;

	/*
	 * Handle 0-3 initial bytes one at a time, so that the loop below starts
	 * with a pointer aligned to four bytes.
	 */
	while (len > 0 && ((uintptr_t) p & 3))
	{
		crc = CRC8(*p++);
		len--;
	}

	/*
	 * Process eight bytes of data at a time.
	 */
	p4 = (const uint32 *) p;
	while (len >= 8)
	{
		uint32		a = *p4++ ^ crc;
		uint32		b = *p4++;

#ifdef WORDS_BIGENDIAN
		const uint8 c0 = b;
		const uint8 c1 = b >> 8;
		const uint8 c2 = b >> 16;
		const uint8 c3 = b >> 24;
		const uint8 c4 = a;
		const uint8 c5 = a >> 8;
		const uint8 c6 = a >> 16;
		const uint8 c7 = a >> 24;
#else
		const uint8 c0 = b >> 24;
		const uint8 c1 = b >> 16;
		const uint8 c2 = b >> 8;
		const uint8 c3 = b;
		const uint8 c4 = a >> 24;
		const uint8 c5 = a >> 16;
		const uint8 c6 = a >> 8;
		const uint8 c7 = a;
#endif

		crc =
			pg_crc32c_table[0][c0] ^ pg_crc32c_table[1][c1] ^
			pg_crc32c_table[2][c2] ^ pg_crc32c_table[3][c3] ^
			pg_crc32c_table[4][c4] ^ pg_crc32c_table[5][c5] ^
			pg_crc32c_table[6][c6] ^ pg_crc32c_table[7][c7];

		len -= 8;
	}

	/*
	 * Handle any remaining bytes one at a time.
	 */
	p = (const unsigned char *) p4;
	while (len > 0)
	{
		crc = CRC8(*p++);
		len--;
	}

	return crc;
}