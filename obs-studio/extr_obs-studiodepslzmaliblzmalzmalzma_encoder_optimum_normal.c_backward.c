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
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t opts_end_index; size_t opts_current_index; TYPE_2__* opts; } ;
typedef  TYPE_1__ lzma_coder ;
struct TYPE_5__ {size_t pos_prev; size_t back_prev; int prev_1_is_literal; size_t pos_prev_2; size_t back_prev_2; scalar_t__ prev_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  make_literal (TYPE_2__*) ; 

__attribute__((used)) static void
backward(lzma_coder *restrict coder, uint32_t *restrict len_res,
		uint32_t *restrict back_res, uint32_t cur)
{
	coder->opts_end_index = cur;

	uint32_t pos_mem = coder->opts[cur].pos_prev;
	uint32_t back_mem = coder->opts[cur].back_prev;

	do {
		if (coder->opts[cur].prev_1_is_literal) {
			make_literal(&coder->opts[pos_mem]);
			coder->opts[pos_mem].pos_prev = pos_mem - 1;

			if (coder->opts[cur].prev_2) {
				coder->opts[pos_mem - 1].prev_1_is_literal
						= false;
				coder->opts[pos_mem - 1].pos_prev
						= coder->opts[cur].pos_prev_2;
				coder->opts[pos_mem - 1].back_prev
						= coder->opts[cur].back_prev_2;
			}
		}

		const uint32_t pos_prev = pos_mem;
		const uint32_t back_cur = back_mem;

		back_mem = coder->opts[pos_prev].back_prev;
		pos_mem = coder->opts[pos_prev].pos_prev;

		coder->opts[pos_prev].back_prev = back_cur;
		coder->opts[pos_prev].pos_prev = cur;
		cur = pos_prev;

	} while (cur != 0);

	coder->opts_current_index = coder->opts[0].pos_prev;
	*len_res = coder->opts[0].pos_prev;
	*back_res = coder->opts[0].back_prev;

	return;
}