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
struct TYPE_5__ {TYPE_1__* filters; } ;
typedef  TYPE_2__ lzma_block ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_4__ {int /*<<< orphan*/ * options; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 size_t LZMA_FILTERS_MAX ; 
 int /*<<< orphan*/  LZMA_VLI_UNKNOWN ; 
 int /*<<< orphan*/  lzma_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_properties(lzma_block *block, lzma_allocator *allocator)
{
	// Free allocated filter options. The last array member is not
	// touched after the initialization in the beginning of
	// lzma_block_header_decode(), so we don't need to touch that here.
	for (size_t i = 0; i < LZMA_FILTERS_MAX; ++i) {
		lzma_free(block->filters[i].options, allocator);
		block->filters[i].id = LZMA_VLI_UNKNOWN;
		block->filters[i].options = NULL;
	}

	return;
}