#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_6__ {TYPE_4__* coder; int /*<<< orphan*/ * memconfig; int /*<<< orphan*/ * get_check; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ lzma_next_coder ;
typedef  int /*<<< orphan*/  lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  sequence; scalar_t__ memlimit; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int LZMA_SUPPORTED_FLAGS ; 
 int /*<<< orphan*/  SEQ_INIT ; 
 int /*<<< orphan*/  auto_decode ; 
 int /*<<< orphan*/  auto_decoder_end ; 
 int /*<<< orphan*/  auto_decoder_get_check ; 
 int /*<<< orphan*/  auto_decoder_memconfig ; 
 TYPE_4__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int),TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lzma_ret
auto_decoder_init(lzma_next_coder *next, lzma_allocator *allocator,
		uint64_t memlimit, uint32_t flags)
{
	lzma_next_coder_init(&auto_decoder_init, next, allocator);

	if (memlimit == 0)
		return LZMA_PROG_ERROR;

	if (flags & ~LZMA_SUPPORTED_FLAGS)
		return LZMA_OPTIONS_ERROR;

	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &auto_decode;
		next->end = &auto_decoder_end;
		next->get_check = &auto_decoder_get_check;
		next->memconfig = &auto_decoder_memconfig;
		next->coder->next = LZMA_NEXT_CODER_INIT;
	}

	next->coder->memlimit = memlimit;
	next->coder->flags = flags;
	next->coder->sequence = SEQ_INIT;

	return LZMA_OK;
}