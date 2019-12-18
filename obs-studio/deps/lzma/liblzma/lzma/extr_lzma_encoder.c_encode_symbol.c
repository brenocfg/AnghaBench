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
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {scalar_t__ read_ahead; } ;
typedef  TYPE_1__ lzma_mf ;
struct TYPE_10__ {scalar_t__ pos_mask; size_t state; int /*<<< orphan*/ * is_rep; int /*<<< orphan*/  rc; int /*<<< orphan*/ ** is_match; } ;
typedef  TYPE_2__ lzma_coder ;

/* Variables and functions */
 scalar_t__ REP_DISTANCES ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  literal (TYPE_2__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  match (TYPE_2__*,scalar_t__ const,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rc_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rep_match (TYPE_2__*,scalar_t__ const,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
encode_symbol(lzma_coder *coder, lzma_mf *mf,
		uint32_t back, uint32_t len, uint32_t position)
{
	const uint32_t pos_state = position & coder->pos_mask;

	if (back == UINT32_MAX) {
		// Literal i.e. eight-bit byte
		assert(len == 1);
		rc_bit(&coder->rc,
				&coder->is_match[coder->state][pos_state], 0);
		literal(coder, mf, position);
	} else {
		// Some type of match
		rc_bit(&coder->rc,
			&coder->is_match[coder->state][pos_state], 1);

		if (back < REP_DISTANCES) {
			// It's a repeated match i.e. the same distance
			// has been used earlier.
			rc_bit(&coder->rc, &coder->is_rep[coder->state], 1);
			rep_match(coder, pos_state, back, len);
		} else {
			// Normal match
			rc_bit(&coder->rc, &coder->is_rep[coder->state], 0);
			match(coder, pos_state, back - REP_DISTANCES, len);
		}
	}

	assert(mf->read_ahead >= len);
	mf->read_ahead -= len;
}