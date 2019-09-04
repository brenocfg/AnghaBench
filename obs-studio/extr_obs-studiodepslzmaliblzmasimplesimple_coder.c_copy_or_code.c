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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ lzma_ret ;
struct TYPE_4__ {scalar_t__ (* code ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t,scalar_t__) ;int /*<<< orphan*/  coder; } ;
struct TYPE_5__ {int end_was_reached; scalar_t__ is_encoder; TYPE_1__ next; } ;
typedef  TYPE_2__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
typedef  scalar_t__ lzma_action ;

/* Variables and functions */
 scalar_t__ LZMA_FINISH ; 
 scalar_t__ const LZMA_OK ; 
 scalar_t__ const LZMA_STREAM_END ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lzma_bufcpy (int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,size_t,int /*<<< orphan*/ *,size_t*,size_t,scalar_t__) ; 

__attribute__((used)) static lzma_ret
copy_or_code(lzma_coder *coder, lzma_allocator *allocator,
		const uint8_t *restrict in, size_t *restrict in_pos,
		size_t in_size, uint8_t *restrict out,
		size_t *restrict out_pos, size_t out_size, lzma_action action)
{
	assert(!coder->end_was_reached);

	if (coder->next.code == NULL) {
		lzma_bufcpy(in, in_pos, in_size, out, out_pos, out_size);

		// Check if end of stream was reached.
		if (coder->is_encoder && action == LZMA_FINISH
				&& *in_pos == in_size)
			coder->end_was_reached = true;

	} else {
		// Call the next coder in the chain to provide us some data.
		const lzma_ret ret = coder->next.code(
				coder->next.coder, allocator,
				in, in_pos, in_size,
				out, out_pos, out_size, action);

		if (ret == LZMA_STREAM_END) {
			assert(!coder->is_encoder
					|| action == LZMA_FINISH);
			coder->end_was_reached = true;

		} else if (ret != LZMA_OK) {
			return ret;
		}
	}

	return LZMA_OK;
}