#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lzma_vli ;
struct TYPE_11__ {int /*<<< orphan*/  check; int /*<<< orphan*/  backward_size; int /*<<< orphan*/  version; } ;
typedef  TYPE_2__ lzma_stream_flags ;
typedef  int /*<<< orphan*/  const lzma_ret ;
struct TYPE_14__ {int /*<<< orphan*/  check; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/  header_size; } ;
struct TYPE_13__ {int /*<<< orphan*/  coder; int /*<<< orphan*/  const (* code ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,size_t,size_t const) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  coder; int /*<<< orphan*/  const (* code ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t,size_t const) ;} ;
struct TYPE_12__ {int sequence; int block_encoder_is_initialized; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer; TYPE_7__ block_options; int /*<<< orphan*/  index; TYPE_6__ index_encoder; TYPE_1__ block_encoder; int /*<<< orphan*/  buffer_pos; } ;
typedef  TYPE_3__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
typedef  size_t const lzma_action ;

/* Variables and functions */
#define  LZMA_FINISH 136 
 int /*<<< orphan*/  const LZMA_OK ; 
 int /*<<< orphan*/  const LZMA_PROG_ERROR ; 
#define  LZMA_RUN 135 
 int /*<<< orphan*/  const LZMA_STREAM_END ; 
 int /*<<< orphan*/  LZMA_STREAM_HEADER_SIZE ; 
#define  LZMA_SYNC_FLUSH 134 
#define  SEQ_BLOCK_ENCODE 133 
#define  SEQ_BLOCK_HEADER 132 
#define  SEQ_BLOCK_INIT 131 
#define  SEQ_INDEX_ENCODE 130 
#define  SEQ_STREAM_FOOTER 129 
#define  SEQ_STREAM_HEADER 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_encoder_init (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const lzma_block_header_encode (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_block_unpadded_size (TYPE_7__*) ; 
 int /*<<< orphan*/  lzma_bufcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,size_t) ; 
 int /*<<< orphan*/  lzma_index_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_index_encoder_init (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_index_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const lzma_stream_footer_encode (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t,size_t const) ; 
 int /*<<< orphan*/  const stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,size_t,size_t const) ; 

__attribute__((used)) static lzma_ret
stream_encode(lzma_coder *coder, lzma_allocator *allocator,
		const uint8_t *restrict in, size_t *restrict in_pos,
		size_t in_size, uint8_t *restrict out,
		size_t *restrict out_pos, size_t out_size, lzma_action action)
{
	// Main loop
	while (*out_pos < out_size)
	switch (coder->sequence) {
	case SEQ_STREAM_HEADER:
	case SEQ_BLOCK_HEADER:
	case SEQ_STREAM_FOOTER:
		lzma_bufcpy(coder->buffer, &coder->buffer_pos,
				coder->buffer_size, out, out_pos, out_size);
		if (coder->buffer_pos < coder->buffer_size)
			return LZMA_OK;

		if (coder->sequence == SEQ_STREAM_FOOTER)
			return LZMA_STREAM_END;

		coder->buffer_pos = 0;
		++coder->sequence;
		break;

	case SEQ_BLOCK_INIT: {
		if (*in_pos == in_size) {
			// If we are requested to flush or finish the current
			// Block, return LZMA_STREAM_END immediately since
			// there's nothing to do.
			if (action != LZMA_FINISH)
				return action == LZMA_RUN
						? LZMA_OK : LZMA_STREAM_END;

			// The application had used LZMA_FULL_FLUSH to finish
			// the previous Block, but now wants to finish without
			// encoding new data, or it is simply creating an
			// empty Stream with no Blocks.
			//
			// Initialize the Index encoder, and continue to
			// actually encoding the Index.
			return_if_error(lzma_index_encoder_init(
					&coder->index_encoder, allocator,
					coder->index));
			coder->sequence = SEQ_INDEX_ENCODE;
			break;
		}

		// Initialize the Block encoder unless it was already
		// initialized by lzma_stream_encoder_init() or
		// stream_encoder_update().
		if (!coder->block_encoder_is_initialized)
			return_if_error(block_encoder_init(coder, allocator));

		// Make it false so that we don't skip the initialization
		// with the next Block.
		coder->block_encoder_is_initialized = false;

		// Encode the Block Header. This shouldn't fail since we have
		// already initialized the Block encoder.
		if (lzma_block_header_encode(&coder->block_options,
				coder->buffer) != LZMA_OK)
			return LZMA_PROG_ERROR;

		coder->buffer_size = coder->block_options.header_size;
		coder->sequence = SEQ_BLOCK_HEADER;
		break;
	}

	case SEQ_BLOCK_ENCODE: {
		static const lzma_action convert[4] = {
			LZMA_RUN,
			LZMA_SYNC_FLUSH,
			LZMA_FINISH,
			LZMA_FINISH,
		};

		const lzma_ret ret = coder->block_encoder.code(
				coder->block_encoder.coder, allocator,
				in, in_pos, in_size,
				out, out_pos, out_size, convert[action]);
		if (ret != LZMA_STREAM_END || action == LZMA_SYNC_FLUSH)
			return ret;

		// Add a new Index Record.
		const lzma_vli unpadded_size = lzma_block_unpadded_size(
				&coder->block_options);
		assert(unpadded_size != 0);
		return_if_error(lzma_index_append(coder->index, allocator,
				unpadded_size,
				coder->block_options.uncompressed_size));

		coder->sequence = SEQ_BLOCK_INIT;
		break;
	}

	case SEQ_INDEX_ENCODE: {
		// Call the Index encoder. It doesn't take any input, so
		// those pointers can be NULL.
		const lzma_ret ret = coder->index_encoder.code(
				coder->index_encoder.coder, allocator,
				NULL, NULL, 0,
				out, out_pos, out_size, LZMA_RUN);
		if (ret != LZMA_STREAM_END)
			return ret;

		// Encode the Stream Footer into coder->buffer.
		const lzma_stream_flags stream_flags = {
			.version = 0,
			.backward_size = lzma_index_size(coder->index),
			.check = coder->block_options.check,
		};

		if (lzma_stream_footer_encode(&stream_flags, coder->buffer)
				!= LZMA_OK)
			return LZMA_PROG_ERROR;

		coder->buffer_size = LZMA_STREAM_HEADER_SIZE;
		coder->sequence = SEQ_STREAM_FOOTER;
		break;
	}

	default:
		assert(0);
		return LZMA_PROG_ERROR;
	}

	return LZMA_OK;
}