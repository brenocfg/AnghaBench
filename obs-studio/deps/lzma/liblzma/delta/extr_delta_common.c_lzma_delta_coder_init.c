#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_9__ {int /*<<< orphan*/  dist; } ;
typedef  TYPE_1__ lzma_options_delta ;
struct TYPE_10__ {TYPE_8__* coder; int /*<<< orphan*/ * end; } ;
typedef  TYPE_2__ lzma_next_coder ;
struct TYPE_11__ {TYPE_1__* options; } ;
typedef  TYPE_3__ lzma_filter_info ;
typedef  int /*<<< orphan*/  lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_12__ {int /*<<< orphan*/  next; int /*<<< orphan*/  history; scalar_t__ pos; int /*<<< orphan*/  distance; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_DELTA_DIST_MAX ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  delta_coder_end ; 
 TYPE_8__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 scalar_t__ lzma_delta_coder_memusage (TYPE_1__*) ; 
 int /*<<< orphan*/  lzma_next_filter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern lzma_ret
lzma_delta_coder_init(lzma_next_coder *next, lzma_allocator *allocator,
		const lzma_filter_info *filters)
{
	// Allocate memory for the decoder if needed.
	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		// End function is the same for encoder and decoder.
		next->end = &delta_coder_end;
		next->coder->next = LZMA_NEXT_CODER_INIT;
	}

	// Validate the options.
	if (lzma_delta_coder_memusage(filters[0].options) == UINT64_MAX)
		return LZMA_OPTIONS_ERROR;

	// Set the delta distance.
	const lzma_options_delta *opt = filters[0].options;
	next->coder->distance = opt->dist;

	// Initialize the rest of the variables.
	next->coder->pos = 0;
	memzero(next->coder->history, LZMA_DELTA_DIST_MAX);

	// Initialize the next decoder in the chain, if any.
	return lzma_next_filter_init(&next->coder->next,
			allocator, filters + 1);
}