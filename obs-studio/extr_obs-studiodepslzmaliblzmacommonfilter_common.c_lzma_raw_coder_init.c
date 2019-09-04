#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lzma_ret ;
typedef  int /*<<< orphan*/  lzma_next_coder ;
struct TYPE_9__ {int /*<<< orphan*/ * init; int /*<<< orphan*/  id; int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ lzma_filter_info ;
typedef  TYPE_2__* (* lzma_filter_find ) (int /*<<< orphan*/ ) ;
struct TYPE_10__ {int /*<<< orphan*/ * init; } ;
typedef  TYPE_2__ lzma_filter_coder ;
struct TYPE_11__ {int /*<<< orphan*/  options; int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ lzma_filter ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_FILTERS_MAX ; 
 scalar_t__ const LZMA_OK ; 
 scalar_t__ LZMA_OPTIONS_ERROR ; 
 int /*<<< orphan*/  LZMA_VLI_UNKNOWN ; 
 int /*<<< orphan*/  lzma_next_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lzma_next_filter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_chain (TYPE_4__ const*,size_t*) ; 

extern lzma_ret
lzma_raw_coder_init(lzma_next_coder *next, lzma_allocator *allocator,
		const lzma_filter *options,
		lzma_filter_find coder_find, bool is_encoder)
{
	// Do some basic validation and get the number of filters.
	size_t count;
	return_if_error(validate_chain(options, &count));

	// Set the filter functions and copy the options pointer.
	lzma_filter_info filters[LZMA_FILTERS_MAX + 1];
	if (is_encoder) {
		for (size_t i = 0; i < count; ++i) {
			// The order of the filters is reversed in the
			// encoder. It allows more efficient handling
			// of the uncompressed data.
			const size_t j = count - i - 1;

			const lzma_filter_coder *const fc
					= coder_find(options[i].id);
			if (fc == NULL || fc->init == NULL)
				return LZMA_OPTIONS_ERROR;

			filters[j].id = options[i].id;
			filters[j].init = fc->init;
			filters[j].options = options[i].options;
		}
	} else {
		for (size_t i = 0; i < count; ++i) {
			const lzma_filter_coder *const fc
					= coder_find(options[i].id);
			if (fc == NULL || fc->init == NULL)
				return LZMA_OPTIONS_ERROR;

			filters[i].id = options[i].id;
			filters[i].init = fc->init;
			filters[i].options = options[i].options;
		}
	}

	// Terminate the array.
	filters[count].id = LZMA_VLI_UNKNOWN;
	filters[count].init = NULL;

	// Initialize the filters.
	const lzma_ret ret = lzma_next_filter_init(next, allocator, filters);
	if (ret != LZMA_OK)
		lzma_next_end(next, allocator);

	return ret;
}