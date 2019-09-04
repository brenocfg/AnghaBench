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
typedef  int lzma_vli ;

/* Variables and functions */
 int COMPRESSED_SIZE_MAX ; 
 int LZMA2_CHUNK_MAX ; 
 int LZMA2_HEADER_UNCOMPRESSED ; 

__attribute__((used)) static lzma_vli
lzma2_bound(lzma_vli uncompressed_size)
{
	// Prevent integer overflow in overhead calculation.
	if (uncompressed_size > COMPRESSED_SIZE_MAX)
		return 0;

	// Calculate the exact overhead of the LZMA2 headers: Round
	// uncompressed_size up to the next multiple of LZMA2_CHUNK_MAX,
	// multiply by the size of per-chunk header, and add one byte for
	// the end marker.
	const lzma_vli overhead = ((uncompressed_size + LZMA2_CHUNK_MAX - 1)
				/ LZMA2_CHUNK_MAX)
			* LZMA2_HEADER_UNCOMPRESSED + 1;

	// Catch the possible integer overflow.
	if (COMPRESSED_SIZE_MAX - overhead < uncompressed_size)
		return 0;

	return uncompressed_size + overhead;
}