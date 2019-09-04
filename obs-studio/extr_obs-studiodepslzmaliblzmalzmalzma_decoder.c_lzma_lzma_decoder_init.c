#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
typedef  int /*<<< orphan*/  lzma_next_coder ;
struct TYPE_4__ {int /*<<< orphan*/ * init; } ;
typedef  TYPE_1__ lzma_filter_info ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_decoder_init ; 
 int /*<<< orphan*/  lzma_lz_decoder_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

extern lzma_ret
lzma_lzma_decoder_init(lzma_next_coder *next, lzma_allocator *allocator,
		const lzma_filter_info *filters)
{
	// LZMA can only be the last filter in the chain. This is enforced
	// by the raw_decoder initialization.
	assert(filters[1].init == NULL);

	return lzma_lz_decoder_init(next, allocator, filters,
			&lzma_decoder_init);
}