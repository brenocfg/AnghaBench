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
struct TYPE_6__ {TYPE_1__* filters; int /*<<< orphan*/  index; int /*<<< orphan*/  index_encoder; int /*<<< orphan*/  block_encoder; } ;
typedef  TYPE_2__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_5__ {scalar_t__ id; TYPE_2__* options; } ;

/* Variables and functions */
 scalar_t__ LZMA_VLI_UNKNOWN ; 
 int /*<<< orphan*/  lzma_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_index_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_next_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
stream_encoder_end(lzma_coder *coder, lzma_allocator *allocator)
{
	lzma_next_end(&coder->block_encoder, allocator);
	lzma_next_end(&coder->index_encoder, allocator);
	lzma_index_end(coder->index, allocator);

	for (size_t i = 0; coder->filters[i].id != LZMA_VLI_UNKNOWN; ++i)
		lzma_free(coder->filters[i].options, allocator);

	lzma_free(coder, allocator);
	return;
}