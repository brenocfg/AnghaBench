#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int uncompressed_size; int compressed_size; int need_properties; int need_dictionary_reset; int* buf; int need_state_reset; size_t buf_pos; int /*<<< orphan*/  opt_cur; } ;
typedef  TYPE_1__ lzma_coder ;

/* Variables and functions */
 int LZMA2_CHUNK_MAX ; 
 scalar_t__ LZMA2_HEADER_MAX ; 
 int LZMA2_UNCOMPRESSED_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lzma_lzma_lclppb_encode (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static void
lzma2_header_lzma(lzma_coder *coder)
{
	assert(coder->uncompressed_size > 0);
	assert(coder->uncompressed_size <= LZMA2_UNCOMPRESSED_MAX);
	assert(coder->compressed_size > 0);
	assert(coder->compressed_size <= LZMA2_CHUNK_MAX);

	size_t pos;

	if (coder->need_properties) {
		pos = 0;

		if (coder->need_dictionary_reset)
			coder->buf[pos] = 0x80 + (3 << 5);
		else
			coder->buf[pos] = 0x80 + (2 << 5);
	} else {
		pos = 1;

		if (coder->need_state_reset)
			coder->buf[pos] = 0x80 + (1 << 5);
		else
			coder->buf[pos] = 0x80;
	}

	// Set the start position for copying.
	coder->buf_pos = pos;

	// Uncompressed size
	size_t size = coder->uncompressed_size - 1;
	coder->buf[pos++] += size >> 16;
	coder->buf[pos++] = (size >> 8) & 0xFF;
	coder->buf[pos++] = size & 0xFF;

	// Compressed size
	size = coder->compressed_size - 1;
	coder->buf[pos++] = size >> 8;
	coder->buf[pos++] = size & 0xFF;

	// Properties, if needed
	if (coder->need_properties)
		lzma_lzma_lclppb_encode(&coder->opt_cur, coder->buf + pos);

	coder->need_properties = false;
	coder->need_state_reset = false;
	coder->need_dictionary_reset = false;

	// The copying code uses coder->compressed_size to indicate the end
	// of coder->buf[], so we need add the maximum size of the header here.
	coder->compressed_size += LZMA2_HEADER_MAX;

	return;
}