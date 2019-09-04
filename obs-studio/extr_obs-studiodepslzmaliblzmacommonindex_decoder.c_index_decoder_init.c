#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_7__ {TYPE_4__* coder; int /*<<< orphan*/ * memconfig; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ lzma_next_coder ;
typedef  int /*<<< orphan*/  lzma_index ;
typedef  int /*<<< orphan*/  lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_8__ {int /*<<< orphan*/ * index; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  index_decode ; 
 int /*<<< orphan*/  index_decoder_end ; 
 int /*<<< orphan*/  index_decoder_memconfig ; 
 int /*<<< orphan*/  index_decoder_reset (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__) ; 
 TYPE_4__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_index_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__),TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lzma_ret
index_decoder_init(lzma_next_coder *next, lzma_allocator *allocator,
		lzma_index **i, uint64_t memlimit)
{
	lzma_next_coder_init(&index_decoder_init, next, allocator);

	if (i == NULL || memlimit == 0)
		return LZMA_PROG_ERROR;

	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &index_decode;
		next->end = &index_decoder_end;
		next->memconfig = &index_decoder_memconfig;
		next->coder->index = NULL;
	} else {
		lzma_index_end(next->coder->index, allocator);
	}

	return index_decoder_reset(next->coder, allocator, i, memlimit);
}