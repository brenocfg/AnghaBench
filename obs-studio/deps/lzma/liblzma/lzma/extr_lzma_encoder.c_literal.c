#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  probability ;
struct TYPE_5__ {size_t read_pos; size_t read_ahead; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ lzma_mf ;
struct TYPE_6__ {int* reps; int /*<<< orphan*/  state; int /*<<< orphan*/  rc; int /*<<< orphan*/  literal_pos_mask; int /*<<< orphan*/  literal_context_bits; int /*<<< orphan*/  literal; } ;
typedef  TYPE_2__ lzma_coder ;

/* Variables and functions */
 scalar_t__ is_literal_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  literal_matched (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * literal_subcoder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_bittree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  update_literal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
literal(lzma_coder *coder, lzma_mf *mf, uint32_t position)
{
	// Locate the literal byte to be encoded and the subcoder.
	const uint8_t cur_byte = mf->buffer[
			mf->read_pos - mf->read_ahead];
	probability *subcoder = literal_subcoder(coder->literal,
			coder->literal_context_bits, coder->literal_pos_mask,
			position, mf->buffer[mf->read_pos - mf->read_ahead - 1]);

	if (is_literal_state(coder->state)) {
		// Previous LZMA-symbol was a literal. Encode a normal
		// literal without a match byte.
		rc_bittree(&coder->rc, subcoder, 8, cur_byte);
	} else {
		// Previous LZMA-symbol was a match. Use the last byte of
		// the match as a "match byte". That is, compare the bits
		// of the current literal and the match byte.
		const uint8_t match_byte = mf->buffer[
				mf->read_pos - coder->reps[0] - 1
				- mf->read_ahead];
		literal_matched(&coder->rc, subcoder, match_byte, cur_byte);
	}

	update_literal(coder->state);
}