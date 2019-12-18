#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_15__ {scalar_t__ read_pos; scalar_t__ read_ahead; scalar_t__ read_limit; scalar_t__ action; } ;
typedef  TYPE_1__ lzma_mf ;
struct TYPE_16__ {int is_flushed; int /*<<< orphan*/  rc; scalar_t__ fast_mode; int /*<<< orphan*/  is_initialized; } ;
typedef  TYPE_2__ lzma_coder ;

/* Variables and functions */
 scalar_t__ LOOP_INPUT_MAX ; 
 scalar_t__ LZMA2_CHUNK_MAX ; 
 int /*<<< orphan*/  LZMA_OK ; 
 scalar_t__ LZMA_RUN ; 
 int /*<<< orphan*/  LZMA_STREAM_END ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  encode_eopm (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  encode_init (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  encode_symbol (TYPE_2__*,TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lzma_lzma_optimum_fast (TYPE_2__*,TYPE_1__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  lzma_lzma_optimum_normal (TYPE_2__*,TYPE_1__*,scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ mf_position (TYPE_1__*) ; 
 scalar_t__ rc_encode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t) ; 
 int /*<<< orphan*/  rc_flush (int /*<<< orphan*/ *) ; 
 scalar_t__ rc_pending (int /*<<< orphan*/ *) ; 

extern lzma_ret
lzma_lzma_encode(lzma_coder *restrict coder, lzma_mf *restrict mf,
		uint8_t *restrict out, size_t *restrict out_pos,
		size_t out_size, uint32_t limit)
{
	// Initialize the stream if no data has been encoded yet.
	if (!coder->is_initialized && !encode_init(coder, mf))
		return LZMA_OK;

	// Get the lowest bits of the uncompressed offset from the LZ layer.
	uint32_t position = mf_position(mf);

	while (true) {
		// Encode pending bits, if any. Calling this before encoding
		// the next symbol is needed only with plain LZMA, since
		// LZMA2 always provides big enough buffer to flush
		// everything out from the range encoder. For the same reason,
		// rc_encode() never returns true when this function is used
		// as part of LZMA2 encoder.
		if (rc_encode(&coder->rc, out, out_pos, out_size)) {
			assert(limit == UINT32_MAX);
			return LZMA_OK;
		}

		// With LZMA2 we need to take care that compressed size of
		// a chunk doesn't get too big.
		// FIXME? Check if this could be improved.
		if (limit != UINT32_MAX
				&& (mf->read_pos - mf->read_ahead >= limit
					|| *out_pos + rc_pending(&coder->rc)
						>= LZMA2_CHUNK_MAX
							- LOOP_INPUT_MAX))
			break;

		// Check that there is some input to process.
		if (mf->read_pos >= mf->read_limit) {
			if (mf->action == LZMA_RUN)
				return LZMA_OK;

			if (mf->read_ahead == 0)
				break;
		}

		// Get optimal match (repeat position and length).
		// Value ranges for pos:
		//   - [0, REP_DISTANCES): repeated match
		//   - [REP_DISTANCES, UINT32_MAX):
		//     match at (pos - REP_DISTANCES)
		//   - UINT32_MAX: not a match but a literal
		// Value ranges for len:
		//   - [MATCH_LEN_MIN, MATCH_LEN_MAX]
		uint32_t len;
		uint32_t back;

		if (coder->fast_mode)
			lzma_lzma_optimum_fast(coder, mf, &back, &len);
		else
			lzma_lzma_optimum_normal(
					coder, mf, &back, &len, position);

		encode_symbol(coder, mf, back, len, position);

		position += len;
	}

	if (!coder->is_flushed) {
		coder->is_flushed = true;

		// We don't support encoding plain LZMA streams without EOPM,
		// and LZMA2 doesn't use EOPM at LZMA level.
		if (limit == UINT32_MAX)
			encode_eopm(coder, position);

		// Flush the remaining bytes from the range encoder.
		rc_flush(&coder->rc);

		// Copy the remaining bytes to the output buffer. If there
		// isn't enough output space, we will copy out the remaining
		// bytes on the next call to this function by using
		// the rc_encode() call in the encoding loop above.
		if (rc_encode(&coder->rc, out, out_pos, out_size)) {
			assert(limit == UINT32_MAX);
			return LZMA_OK;
		}
	}

	// Make it ready for the next LZMA2 chunk.
	coder->is_flushed = false;

	return LZMA_STREAM_END;
}