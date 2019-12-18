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
typedef  int /*<<< orphan*/  uint64 ;
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ pg_crc32c ;

/* Variables and functions */
 scalar_t__ _mm_crc32_u32 (scalar_t__,unsigned int const) ; 
 scalar_t__ _mm_crc32_u64 (scalar_t__,int /*<<< orphan*/  const) ; 
 scalar_t__ _mm_crc32_u8 (scalar_t__,unsigned char const) ; 

pg_crc32c
pg_comp_crc32c_sse42(pg_crc32c crc, const void *data, size_t len)
{
	const unsigned char *p = data;
	const unsigned char *pend = p + len;

	/*
	 * Process eight bytes of data at a time.
	 *
	 * NB: We do unaligned accesses here. The Intel architecture allows that,
	 * and performance testing didn't show any performance gain from aligning
	 * the begin address.
	 */
#ifdef __x86_64__
	while (p + 8 <= pend)
	{
		crc = (uint32) _mm_crc32_u64(crc, *((const uint64 *) p));
		p += 8;
	}

	/* Process remaining full four bytes if any */
	if (p + 4 <= pend)
	{
		crc = _mm_crc32_u32(crc, *((const unsigned int *) p));
		p += 4;
	}
#else

	/*
	 * Process four bytes at a time. (The eight byte instruction is not
	 * available on the 32-bit x86 architecture).
	 */
	while (p + 4 <= pend)
	{
		crc = _mm_crc32_u32(crc, *((const unsigned int *) p));
		p += 4;
	}
#endif							/* __x86_64__ */

	/* Process any remaining bytes one at a time. */
	while (p < pend)
	{
		crc = _mm_crc32_u8(crc, *p);
		p++;
	}

	return crc;
}