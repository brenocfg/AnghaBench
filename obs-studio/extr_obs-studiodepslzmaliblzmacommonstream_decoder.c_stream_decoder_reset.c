#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_3__ {scalar_t__ pos; int /*<<< orphan*/  sequence; int /*<<< orphan*/ * index_hash; } ;
typedef  TYPE_1__ lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  SEQ_STREAM_HEADER ; 
 int /*<<< orphan*/ * lzma_index_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lzma_ret
stream_decoder_reset(lzma_coder *coder, lzma_allocator *allocator)
{
	// Initialize the Index hash used to verify the Index.
	coder->index_hash = lzma_index_hash_init(coder->index_hash, allocator);
	if (coder->index_hash == NULL)
		return LZMA_MEM_ERROR;

	// Reset the rest of the variables.
	coder->sequence = SEQ_STREAM_HEADER;
	coder->pos = 0;

	return LZMA_OK;
}