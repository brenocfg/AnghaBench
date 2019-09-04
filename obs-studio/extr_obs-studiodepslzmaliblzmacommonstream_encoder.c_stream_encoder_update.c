#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lzma_ret ;
struct TYPE_15__ {scalar_t__ id; int /*<<< orphan*/  options; } ;
typedef  TYPE_3__ lzma_filter ;
struct TYPE_14__ {int /*<<< orphan*/  coder; int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__ const*,TYPE_3__ const*) ;} ;
struct TYPE_13__ {TYPE_3__* filters; } ;
struct TYPE_16__ {scalar_t__ sequence; int block_encoder_is_initialized; TYPE_3__* filters; TYPE_2__ block_encoder; TYPE_1__ block_options; } ;
typedef  TYPE_4__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 scalar_t__ const LZMA_OK ; 
 scalar_t__ LZMA_PROG_ERROR ; 
 scalar_t__ LZMA_VLI_UNKNOWN ; 
 scalar_t__ SEQ_BLOCK_ENCODE ; 
 scalar_t__ SEQ_BLOCK_INIT ; 
 scalar_t__ block_encoder_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lzma_filters_copy (TYPE_3__ const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__ const*,TYPE_3__ const*) ; 

__attribute__((used)) static lzma_ret
stream_encoder_update(lzma_coder *coder, lzma_allocator *allocator,
		const lzma_filter *filters,
		const lzma_filter *reversed_filters)
{
	if (coder->sequence <= SEQ_BLOCK_INIT) {
		// There is no incomplete Block waiting to be finished,
		// thus we can change the whole filter chain. Start by
		// trying to initialize the Block encoder with the new
		// chain. This way we detect if the chain is valid.
		coder->block_encoder_is_initialized = false;
		coder->block_options.filters = (lzma_filter *)(filters);
		const lzma_ret ret = block_encoder_init(coder, allocator);
		coder->block_options.filters = coder->filters;
		if (ret != LZMA_OK)
			return ret;

		coder->block_encoder_is_initialized = true;

	} else if (coder->sequence <= SEQ_BLOCK_ENCODE) {
		// We are in the middle of a Block. Try to update only
		// the filter-specific options.
		return_if_error(coder->block_encoder.update(
				coder->block_encoder.coder, allocator,
				filters, reversed_filters));
	} else {
		// Trying to update the filter chain when we are already
		// encoding Index or Stream Footer.
		return LZMA_PROG_ERROR;
	}

	// Free the copy of the old chain and make a copy of the new chain.
	for (size_t i = 0; coder->filters[i].id != LZMA_VLI_UNKNOWN; ++i)
		lzma_free(coder->filters[i].options, allocator);

	return lzma_filters_copy(filters, coder->filters, allocator);
}