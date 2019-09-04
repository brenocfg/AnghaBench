#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_9__ {scalar_t__ preset_dict_size; int /*<<< orphan*/ * preset_dict; } ;
typedef  TYPE_1__ lzma_options_lzma ;
struct TYPE_10__ {scalar_t__ before_size; scalar_t__ dict_size; } ;
typedef  TYPE_2__ lzma_lz_options ;
struct TYPE_11__ {TYPE_6__* coder; int /*<<< orphan*/ * options_update; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; } ;
typedef  TYPE_3__ lzma_lz_encoder ;
typedef  int /*<<< orphan*/  lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_12__ {int need_properties; int need_state_reset; int need_dictionary_reset; TYPE_1__ opt_cur; int /*<<< orphan*/ * lzma; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 scalar_t__ LZMA2_CHUNK_MAX ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 int /*<<< orphan*/  SEQ_INIT ; 
 int /*<<< orphan*/  lzma2_encode ; 
 int /*<<< orphan*/  lzma2_encoder_end ; 
 int /*<<< orphan*/  lzma2_encoder_options_update ; 
 TYPE_6__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_lzma_encoder_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  return_if_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lzma_ret
lzma2_encoder_init(lzma_lz_encoder *lz, lzma_allocator *allocator,
		const void *options, lzma_lz_options *lz_options)
{
	if (options == NULL)
		return LZMA_PROG_ERROR;

	if (lz->coder == NULL) {
		lz->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (lz->coder == NULL)
			return LZMA_MEM_ERROR;

		lz->code = &lzma2_encode;
		lz->end = &lzma2_encoder_end;
		lz->options_update = &lzma2_encoder_options_update;

		lz->coder->lzma = NULL;
	}

	lz->coder->opt_cur = *(const lzma_options_lzma *)(options);

	lz->coder->sequence = SEQ_INIT;
	lz->coder->need_properties = true;
	lz->coder->need_state_reset = false;
	lz->coder->need_dictionary_reset
			= lz->coder->opt_cur.preset_dict == NULL
			|| lz->coder->opt_cur.preset_dict_size == 0;

	// Initialize LZMA encoder
	return_if_error(lzma_lzma_encoder_create(&lz->coder->lzma, allocator,
			&lz->coder->opt_cur, lz_options));

	// Make sure that we will always have enough history available in
	// case we need to use uncompressed chunks. They are used when the
	// compressed size of a chunk is not smaller than the uncompressed
	// size, so we need to have at least LZMA2_COMPRESSED_MAX bytes
	// history available.
	if (lz_options->before_size + lz_options->dict_size < LZMA2_CHUNK_MAX)
		lz_options->before_size
				= LZMA2_CHUNK_MAX - lz_options->dict_size;

	return LZMA_OK;
}