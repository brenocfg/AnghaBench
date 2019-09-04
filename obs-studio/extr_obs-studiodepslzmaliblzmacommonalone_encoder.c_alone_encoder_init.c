#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_12__ {scalar_t__ dict_size; } ;
typedef  TYPE_1__ lzma_options_lzma ;
struct TYPE_13__ {TYPE_9__* coder; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; } ;
typedef  TYPE_2__ lzma_next_coder ;
struct TYPE_14__ {void* options; int /*<<< orphan*/ * init; } ;
typedef  TYPE_3__ lzma_filter_info ;
typedef  int /*<<< orphan*/  lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_15__ {int /*<<< orphan*/  next; scalar_t__ header; scalar_t__ header_pos; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 scalar_t__ LZMA_DICT_SIZE_MIN ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int /*<<< orphan*/  SEQ_HEADER ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  alone_encode ; 
 int /*<<< orphan*/  alone_encoder_end ; 
 TYPE_9__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_lzma_encoder_init ; 
 scalar_t__ lzma_lzma_lclppb_encode (TYPE_1__ const*,scalar_t__) ; 
 int /*<<< orphan*/  lzma_next_coder_init (int /*<<< orphan*/  (*) (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__ const*),TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_next_filter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  unaligned_write32le (scalar_t__,int) ; 

__attribute__((used)) static lzma_ret
alone_encoder_init(lzma_next_coder *next, lzma_allocator *allocator,
		const lzma_options_lzma *options)
{
	lzma_next_coder_init(&alone_encoder_init, next, allocator);

	if (next->coder == NULL) {
		next->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (next->coder == NULL)
			return LZMA_MEM_ERROR;

		next->code = &alone_encode;
		next->end = &alone_encoder_end;
		next->coder->next = LZMA_NEXT_CODER_INIT;
	}

	// Basic initializations
	next->coder->sequence = SEQ_HEADER;
	next->coder->header_pos = 0;

	// Encode the header:
	// - Properties (1 byte)
	if (lzma_lzma_lclppb_encode(options, next->coder->header))
		return LZMA_OPTIONS_ERROR;

	// - Dictionary size (4 bytes)
	if (options->dict_size < LZMA_DICT_SIZE_MIN)
		return LZMA_OPTIONS_ERROR;

	// Round up to the next 2^n or 2^n + 2^(n - 1) depending on which
	// one is the next unless it is UINT32_MAX. While the header would
	// allow any 32-bit integer, we do this to keep the decoder of liblzma
	// accepting the resulting files.
	uint32_t d = options->dict_size - 1;
	d |= d >> 2;
	d |= d >> 3;
	d |= d >> 4;
	d |= d >> 8;
	d |= d >> 16;
	if (d != UINT32_MAX)
		++d;

	unaligned_write32le(next->coder->header + 1, d);

	// - Uncompressed size (always unknown and using EOPM)
	memset(next->coder->header + 1 + 4, 0xFF, 8);

	// Initialize the LZMA encoder.
	const lzma_filter_info filters[2] = {
		{
			.init = &lzma_lzma_encoder_init,
			.options = (void *)(options),
		}, {
			.init = NULL,
		}
	};

	return lzma_next_filter_init(&next->coder->next, allocator, filters);
}