#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ lzma_ret ;
struct TYPE_8__ {scalar_t__ pos; scalar_t__ size; size_t limit; scalar_t__ need_reset; scalar_t__ buf; } ;
struct TYPE_6__ {scalar_t__ (* code ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/  const*,size_t*,size_t) ;int /*<<< orphan*/  coder; } ;
struct TYPE_7__ {TYPE_3__ dict; TYPE_1__ lz; } ;
typedef  TYPE_2__ lzma_coder ;

/* Variables and functions */
 scalar_t__ const LZMA_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lz_decoder_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t const) ; 
 size_t my_min (size_t,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/  const*,size_t*,size_t) ; 

__attribute__((used)) static lzma_ret
decode_buffer(lzma_coder *coder,
		const uint8_t *restrict in, size_t *restrict in_pos,
		size_t in_size, uint8_t *restrict out,
		size_t *restrict out_pos, size_t out_size)
{
	while (true) {
		// Wrap the dictionary if needed.
		if (coder->dict.pos == coder->dict.size)
			coder->dict.pos = 0;

		// Store the current dictionary position. It is needed to know
		// where to start copying to the out[] buffer.
		const size_t dict_start = coder->dict.pos;

		// Calculate how much we allow coder->lz.code() to decode.
		// It must not decode past the end of the dictionary
		// buffer, and we don't want it to decode more than is
		// actually needed to fill the out[] buffer.
		coder->dict.limit = coder->dict.pos
				+ my_min(out_size - *out_pos,
					coder->dict.size - coder->dict.pos);

		// Call the coder->lz.code() to do the actual decoding.
		const lzma_ret ret = coder->lz.code(
				coder->lz.coder, &coder->dict,
				in, in_pos, in_size);

		// Copy the decoded data from the dictionary to the out[]
		// buffer.
		const size_t copy_size = coder->dict.pos - dict_start;
		assert(copy_size <= out_size - *out_pos);
		memcpy(out + *out_pos, coder->dict.buf + dict_start,
				copy_size);
		*out_pos += copy_size;

		// Reset the dictionary if so requested by coder->lz.code().
		if (coder->dict.need_reset) {
			lz_decoder_reset(coder);

			// Since we reset dictionary, we don't check if
			// dictionary became full.
			if (ret != LZMA_OK || *out_pos == out_size)
				return ret;
		} else {
			// Return if everything got decoded or an error
			// occurred, or if there's no more data to decode.
			//
			// Note that detecting if there's something to decode
			// is done by looking if dictionary become full
			// instead of looking if *in_pos == in_size. This
			// is because it is possible that all the input was
			// consumed already but some data is pending to be
			// written to the dictionary.
			if (ret != LZMA_OK || *out_pos == out_size
					|| coder->dict.pos < coder->dict.size)
				return ret;
		}
	}
}