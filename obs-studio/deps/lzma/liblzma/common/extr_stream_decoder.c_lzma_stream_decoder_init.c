#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_7__ {TYPE_2__* coder; int /*<<< orphan*/ * memconfig; int /*<<< orphan*/ * get_check; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ lzma_next_coder ;
typedef  int /*<<< orphan*/  lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_8__ {int tell_no_check; int tell_unsupported_check; int tell_any_check; int concatenated; int first_stream; int /*<<< orphan*/  memusage; scalar_t__ memlimit; int /*<<< orphan*/ * index_hash; int /*<<< orphan*/  block_decoder; } ;

/* Variables and functions */
 int LZMA_CONCATENATED ; 
 int /*<<< orphan*/  LZMA_MEMUSAGE_BASE ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int LZMA_SUPPORTED_FLAGS ; 
 int LZMA_TELL_ANY_CHECK ; 
 int LZMA_TELL_NO_CHECK ; 
 int LZMA_TELL_UNSUPPORTED_CHECK ; 
 TYPE_2__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int),TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_decode ; 
 int /*<<< orphan*/  stream_decoder_end ; 
 int /*<<< orphan*/  stream_decoder_get_check ; 
 int /*<<< orphan*/  stream_decoder_memconfig ; 
 int /*<<< orphan*/  stream_decoder_reset (TYPE_2__*,int /*<<< orphan*/ *) ; 

extern lzma_ret
lzma_stream_decoder_init(lzma_next_coder *next, lzma_allocator *allocator,
		uint64_t memlimit, uint32_t flags)
{
	lzma_next_coder_init(&lzma_stream_decoder_init, next, allocator);

	if (memlimit == 0)
		return LZMA_PROG_ERROR;

	if (flags & ~LZMA_SUPPORTED_FLAGS)
		return LZMA_OPTIONS_ERROR;

	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &stream_decode;
		next->end = &stream_decoder_end;
		next->get_check = &stream_decoder_get_check;
		next->memconfig = &stream_decoder_memconfig;

		next->coder->block_decoder = LZMA_NEXT_CODER_INIT;
		next->coder->index_hash = NULL;
	}

	next->coder->memlimit = memlimit;
	next->coder->memusage = LZMA_MEMUSAGE_BASE;
	next->coder->tell_no_check = (flags & LZMA_TELL_NO_CHECK) != 0;
	next->coder->tell_unsupported_check
			= (flags & LZMA_TELL_UNSUPPORTED_CHECK) != 0;
	next->coder->tell_any_check = (flags & LZMA_TELL_ANY_CHECK) != 0;
	next->coder->concatenated = (flags & LZMA_CONCATENATED) != 0;
	next->coder->first_stream = true;

	return stream_decoder_reset(next->coder, allocator);
}