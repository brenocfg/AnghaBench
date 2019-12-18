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
typedef  scalar_t__ lzma_vli ;

/* Variables and functions */
 int LZMA_STREAM_HEADER_SIZE ; 
 scalar_t__ LZMA_VLI_MAX ; 
 scalar_t__ LZMA_VLI_UNKNOWN ; 
 scalar_t__ index_size (scalar_t__,scalar_t__) ; 
 scalar_t__ vli_ceil4 (scalar_t__) ; 

__attribute__((used)) static lzma_vli
index_file_size(lzma_vli compressed_base, lzma_vli unpadded_sum,
		lzma_vli record_count, lzma_vli index_list_size,
		lzma_vli stream_padding)
{
	// Earlier Streams and Stream Paddings + Stream Header
	// + Blocks + Index + Stream Footer + Stream Padding
	//
	// This might go over LZMA_VLI_MAX due to too big unpadded_sum
	// when this function is used in lzma_index_append().
	lzma_vli file_size = compressed_base + 2 * LZMA_STREAM_HEADER_SIZE
			+ stream_padding + vli_ceil4(unpadded_sum);
	if (file_size > LZMA_VLI_MAX)
		return LZMA_VLI_UNKNOWN;

	// The same applies here.
	file_size += index_size(record_count, index_list_size);
	if (file_size > LZMA_VLI_MAX)
		return LZMA_VLI_UNKNOWN;

	return file_size;
}