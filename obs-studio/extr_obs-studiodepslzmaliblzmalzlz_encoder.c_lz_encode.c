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
struct TYPE_8__ {scalar_t__ action; scalar_t__ read_pos; scalar_t__ read_limit; } ;
struct TYPE_6__ {scalar_t__ (* code ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,size_t*,size_t) ;int /*<<< orphan*/  coder; } ;
struct TYPE_7__ {TYPE_3__ mf; TYPE_1__ lz; } ;
typedef  TYPE_2__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
typedef  scalar_t__ lzma_action ;

/* Variables and functions */
 scalar_t__ const LZMA_OK ; 
 scalar_t__ LZMA_RUN ; 
 int /*<<< orphan*/  fill_window (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,size_t*,size_t) ; 

__attribute__((used)) static lzma_ret
lz_encode(lzma_coder *coder, lzma_allocator *allocator,
		const uint8_t *restrict in, size_t *restrict in_pos,
		size_t in_size,
		uint8_t *restrict out, size_t *restrict out_pos,
		size_t out_size, lzma_action action)
{
	while (*out_pos < out_size
			&& (*in_pos < in_size || action != LZMA_RUN)) {
		// Read more data to coder->mf.buffer if needed.
		if (coder->mf.action == LZMA_RUN && coder->mf.read_pos
				>= coder->mf.read_limit)
			return_if_error(fill_window(coder, allocator,
					in, in_pos, in_size, action));

		// Encode
		const lzma_ret ret = coder->lz.code(coder->lz.coder,
				&coder->mf, out, out_pos, out_size);
		if (ret != LZMA_OK) {
			// Setting this to LZMA_RUN for cases when we are
			// flushing. It doesn't matter when finishing or if
			// an error occurred.
			coder->mf.action = LZMA_RUN;
			return ret;
		}
	}

	return LZMA_OK;
}