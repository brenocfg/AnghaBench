#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_8__ {TYPE_6__* coder; int /*<<< orphan*/ * memconfig; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; } ;
typedef  TYPE_2__ lzma_next_coder ;
typedef  int /*<<< orphan*/  lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_7__ {scalar_t__ preset_dict_size; int /*<<< orphan*/ * preset_dict; scalar_t__ dict_size; } ;
struct TYPE_9__ {int picky; int /*<<< orphan*/  memusage; scalar_t__ memlimit; scalar_t__ uncompressed_size; TYPE_1__ options; scalar_t__ pos; int /*<<< orphan*/  sequence; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEMUSAGE_BASE ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  SEQ_PROPERTIES ; 
 int /*<<< orphan*/  alone_decode ; 
 int /*<<< orphan*/  alone_decoder_end ; 
 int /*<<< orphan*/  alone_decoder_memconfig ; 
 TYPE_6__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int),TYPE_2__*,int /*<<< orphan*/ *) ; 

extern lzma_ret
lzma_alone_decoder_init(lzma_next_coder *next, lzma_allocator *allocator,
		uint64_t memlimit, bool picky)
{
	lzma_next_coder_init(&lzma_alone_decoder_init, next, allocator);

	if (memlimit == 0)
		return LZMA_PROG_ERROR;

	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &alone_decode;
		next->end = &alone_decoder_end;
		next->memconfig = &alone_decoder_memconfig;
		next->coder->next = LZMA_NEXT_CODER_INIT;
	}

	next->coder->sequence = SEQ_PROPERTIES;
	next->coder->picky = picky;
	next->coder->pos = 0;
	next->coder->options.dict_size = 0;
	next->coder->options.preset_dict = NULL;
	next->coder->options.preset_dict_size = 0;
	next->coder->uncompressed_size = 0;
	next->coder->memlimit = memlimit;
	next->coder->memusage = LZMA_MEMUSAGE_BASE;

	return LZMA_OK;
}