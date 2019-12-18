#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  check; int /*<<< orphan*/  version; } ;
typedef  TYPE_3__ lzma_stream_flags ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_14__ {TYPE_5__* coder; int /*<<< orphan*/  (* update ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; } ;
typedef  TYPE_4__ lzma_next_coder ;
typedef  int /*<<< orphan*/  lzma_filter ;
typedef  int /*<<< orphan*/  lzma_coder ;
typedef  int /*<<< orphan*/  lzma_check ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_12__ {int /*<<< orphan*/  check; scalar_t__ version; } ;
struct TYPE_15__ {int /*<<< orphan*/  buffer_size; scalar_t__ buffer_pos; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * index; TYPE_2__ block_options; int /*<<< orphan*/  sequence; void* index_encoder; void* block_encoder; TYPE_1__* filters; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 void* LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  LZMA_STREAM_HEADER_SIZE ; 
 int /*<<< orphan*/  LZMA_VLI_UNKNOWN ; 
 int /*<<< orphan*/  SEQ_STREAM_HEADER ; 
 TYPE_5__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_index_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lzma_index_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ),TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_stream_header_encode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_encode ; 
 int /*<<< orphan*/  stream_encoder_end ; 
 int /*<<< orphan*/  stream_encoder_update (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

extern lzma_ret
lzma_stream_encoder_init(lzma_next_coder *next, lzma_allocator *allocator,
		const lzma_filter *filters, lzma_check check)
{
	lzma_next_coder_init(&lzma_stream_encoder_init, next, allocator);

	if (filters == NULL)
		return LZMA_PROG_ERROR;

	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &stream_encode;
		next->end = &stream_encoder_end;
		next->update = &stream_encoder_update;

		next->coder->filters[0].id = LZMA_VLI_UNKNOWN;
		next->coder->block_encoder = LZMA_NEXT_CODER_INIT;
		next->coder->index_encoder = LZMA_NEXT_CODER_INIT;
		next->coder->index = NULL;
	}

	// Basic initializations
	next->coder->sequence = SEQ_STREAM_HEADER;
	next->coder->block_options.version = 0;
	next->coder->block_options.check = check;

	// Initialize the Index
	lzma_index_end(next->coder->index, allocator);
	next->coder->index = lzma_index_init(allocator);
	if (next->coder->index == NULL)
		return LZMA_MEM_ERROR;

	// Encode the Stream Header
	lzma_stream_flags stream_flags = {
		.version = 0,
		.check = check,
	};
	return_if_error(lzma_stream_header_encode(
			&stream_flags, next->coder->buffer));

	next->coder->buffer_pos = 0;
	next->coder->buffer_size = LZMA_STREAM_HEADER_SIZE;

	// Initialize the Block encoder. This way we detect unsupported
	// filter chains when initializing the Stream encoder instead of
	// giving an error after Stream Header has already written out.
	return stream_encoder_update(
			next->coder, allocator, filters, NULL);
}