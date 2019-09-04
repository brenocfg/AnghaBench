#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  const lzma_ret ;
typedef  int /*<<< orphan*/  lzma_dict ;
struct TYPE_4__ {int /*<<< orphan*/  coder; int /*<<< orphan*/  const (* code ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const*,size_t*,size_t) ;int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_uncompressed ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int sequence; int need_properties; int need_dictionary_reset; int uncompressed_size; int next_sequence; int compressed_size; TYPE_1__ lzma; int /*<<< orphan*/  options; } ;
typedef  TYPE_2__ lzma_coder ;

/* Variables and functions */
 int /*<<< orphan*/  const LZMA_DATA_ERROR ; 
 int /*<<< orphan*/  const LZMA_OK ; 
 int /*<<< orphan*/  const LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  const LZMA_STREAM_END ; 
#define  SEQ_COMPRESSED_0 135 
#define  SEQ_COMPRESSED_1 134 
#define  SEQ_CONTROL 133 
#define  SEQ_COPY 132 
#define  SEQ_LZMA 131 
#define  SEQ_PROPERTIES 130 
#define  SEQ_UNCOMPRESSED_1 129 
#define  SEQ_UNCOMPRESSED_2 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dict_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dict_write (int /*<<< orphan*/ *,int const*,size_t*,size_t,size_t const*) ; 
 int /*<<< orphan*/  lzma_lzma_lclppb_decode (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const*,size_t*,size_t) ; 

__attribute__((used)) static lzma_ret
lzma2_decode(lzma_coder *restrict coder, lzma_dict *restrict dict,
		const uint8_t *restrict in, size_t *restrict in_pos,
		size_t in_size)
{
	// With SEQ_LZMA it is possible that no new input is needed to do
	// some progress. The rest of the sequences assume that there is
	// at least one byte of input.
	while (*in_pos < in_size || coder->sequence == SEQ_LZMA)
	switch (coder->sequence) {
	case SEQ_CONTROL: {
		const uint32_t control = in[*in_pos];
		++*in_pos;

		// End marker
		if (control == 0x00)
			return LZMA_STREAM_END;

		if (control >= 0xE0 || control == 1) {
			// Dictionary reset implies that next LZMA chunk has
			// to set new properties.
			coder->need_properties = true;
			coder->need_dictionary_reset = true;
		} else if (coder->need_dictionary_reset) {
			return LZMA_DATA_ERROR;
		}

		if (control >= 0x80) {
			// LZMA chunk. The highest five bits of the
			// uncompressed size are taken from the control byte.
			coder->uncompressed_size = (control & 0x1F) << 16;
			coder->sequence = SEQ_UNCOMPRESSED_1;

			// See if there are new properties or if we need to
			// reset the state.
			if (control >= 0xC0) {
				// When there are new properties, state reset
				// is done at SEQ_PROPERTIES.
				coder->need_properties = false;
				coder->next_sequence = SEQ_PROPERTIES;

			} else if (coder->need_properties) {
				return LZMA_DATA_ERROR;

			} else {
				coder->next_sequence = SEQ_LZMA;

				// If only state reset is wanted with old
				// properties, do the resetting here for
				// simplicity.
				if (control >= 0xA0)
					coder->lzma.reset(coder->lzma.coder,
							&coder->options);
			}
		} else {
			// Invalid control values
			if (control > 2)
				return LZMA_DATA_ERROR;

			// It's uncompressed chunk
			coder->sequence = SEQ_COMPRESSED_0;
			coder->next_sequence = SEQ_COPY;
		}

		if (coder->need_dictionary_reset) {
			// Finish the dictionary reset and let the caller
			// flush the dictionary to the actual output buffer.
			coder->need_dictionary_reset = false;
			dict_reset(dict);
			return LZMA_OK;
		}

		break;
	}

	case SEQ_UNCOMPRESSED_1:
		coder->uncompressed_size += (uint32_t)(in[(*in_pos)++]) << 8;
		coder->sequence = SEQ_UNCOMPRESSED_2;
		break;

	case SEQ_UNCOMPRESSED_2:
		coder->uncompressed_size += in[(*in_pos)++] + 1;
		coder->sequence = SEQ_COMPRESSED_0;
		coder->lzma.set_uncompressed(coder->lzma.coder,
				coder->uncompressed_size);
		break;

	case SEQ_COMPRESSED_0:
		coder->compressed_size = (uint32_t)(in[(*in_pos)++]) << 8;
		coder->sequence = SEQ_COMPRESSED_1;
		break;

	case SEQ_COMPRESSED_1:
		coder->compressed_size += in[(*in_pos)++] + 1;
		coder->sequence = coder->next_sequence;
		break;

	case SEQ_PROPERTIES:
		if (lzma_lzma_lclppb_decode(&coder->options, in[(*in_pos)++]))
			return LZMA_DATA_ERROR;

		coder->lzma.reset(coder->lzma.coder, &coder->options);

		coder->sequence = SEQ_LZMA;
		break;

	case SEQ_LZMA: {
		// Store the start offset so that we can update
		// coder->compressed_size later.
		const size_t in_start = *in_pos;

		// Decode from in[] to *dict.
		const lzma_ret ret = coder->lzma.code(coder->lzma.coder,
				dict, in, in_pos, in_size);

		// Validate and update coder->compressed_size.
		const size_t in_used = *in_pos - in_start;
		if (in_used > coder->compressed_size)
			return LZMA_DATA_ERROR;

		coder->compressed_size -= in_used;

		// Return if we didn't finish the chunk, or an error occurred.
		if (ret != LZMA_STREAM_END)
			return ret;

		// The LZMA decoder must have consumed the whole chunk now.
		// We don't need to worry about uncompressed size since it
		// is checked by the LZMA decoder.
		if (coder->compressed_size != 0)
			return LZMA_DATA_ERROR;

		coder->sequence = SEQ_CONTROL;
		break;
	}

	case SEQ_COPY: {
		// Copy from input to the dictionary as is.
		dict_write(dict, in, in_pos, in_size, &coder->compressed_size);
		if (coder->compressed_size != 0)
			return LZMA_OK;

		coder->sequence = SEQ_CONTROL;
		break;
	}

	default:
		assert(0);
		return LZMA_PROG_ERROR;
	}

	return LZMA_OK;
}