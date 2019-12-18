#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ lzma_ret ;
struct TYPE_9__ {scalar_t__ (* code ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  coder; } ;
typedef  TYPE_1__ lzma_next_coder ;
struct TYPE_10__ {scalar_t__ compressed_size; size_t uncompressed_size; size_t header_size; int /*<<< orphan*/  filters; } ;
typedef  TYPE_2__ lzma_block ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 scalar_t__ LZMA_BUF_ERROR ; 
 scalar_t__ LZMA_DATA_ERROR ; 
 int /*<<< orphan*/  LZMA_FINISH ; 
 TYPE_1__ LZMA_NEXT_CODER_INIT ; 
 scalar_t__ LZMA_OK ; 
 scalar_t__ LZMA_PROG_ERROR ; 
 scalar_t__ LZMA_STREAM_END ; 
 scalar_t__ lzma2_bound (size_t) ; 
 scalar_t__ lzma_block_header_encode (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_block_header_size (TYPE_2__*) ; 
 int /*<<< orphan*/  lzma_next_end (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lzma_raw_encoder_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static lzma_ret
block_encode_normal(lzma_block *block, lzma_allocator *allocator,
		const uint8_t *in, size_t in_size,
		uint8_t *out, size_t *out_pos, size_t out_size)
{
	// Find out the size of the Block Header.
	block->compressed_size = lzma2_bound(in_size);
	if (block->compressed_size == 0)
		return LZMA_DATA_ERROR;

	block->uncompressed_size = in_size;
	return_if_error(lzma_block_header_size(block));

	// Reserve space for the Block Header and skip it for now.
	if (out_size - *out_pos <= block->header_size)
		return LZMA_BUF_ERROR;

	const size_t out_start = *out_pos;
	*out_pos += block->header_size;

	// Limit out_size so that we stop encoding if the output would grow
	// bigger than what uncompressed Block would be.
	if (out_size - *out_pos > block->compressed_size)
		out_size = *out_pos + block->compressed_size;

	// TODO: In many common cases this could be optimized to use
	// significantly less memory.
	lzma_next_coder raw_encoder = LZMA_NEXT_CODER_INIT;
	lzma_ret ret = lzma_raw_encoder_init(
			&raw_encoder, allocator, block->filters);

	if (ret == LZMA_OK) {
		size_t in_pos = 0;
		ret = raw_encoder.code(raw_encoder.coder, allocator,
				in, &in_pos, in_size, out, out_pos, out_size,
				LZMA_FINISH);
	}

	// NOTE: This needs to be run even if lzma_raw_encoder_init() failed.
	lzma_next_end(&raw_encoder, allocator);

	if (ret == LZMA_STREAM_END) {
		// Compression was successful. Write the Block Header.
		block->compressed_size
				= *out_pos - (out_start + block->header_size);
		ret = lzma_block_header_encode(block, out + out_start);
		if (ret != LZMA_OK)
			ret = LZMA_PROG_ERROR;

	} else if (ret == LZMA_OK) {
		// Output buffer became full.
		ret = LZMA_BUF_ERROR;
	}

	// Reset *out_pos if something went wrong.
	if (ret != LZMA_OK)
		*out_pos = out_start;

	return ret;
}