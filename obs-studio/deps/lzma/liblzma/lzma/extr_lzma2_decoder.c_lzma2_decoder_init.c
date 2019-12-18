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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_6__ {scalar_t__ preset_dict_size; int /*<<< orphan*/ * preset_dict; } ;
typedef  TYPE_1__ lzma_options_lzma ;
typedef  int /*<<< orphan*/  lzma_lz_options ;
struct TYPE_7__ {TYPE_4__* coder; int /*<<< orphan*/ * end; int /*<<< orphan*/ * code; } ;
typedef  TYPE_2__ lzma_lz_decoder ;
typedef  int /*<<< orphan*/  lzma_coder ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_8__ {int need_properties; int need_dictionary_reset; int /*<<< orphan*/  lzma; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_LZ_DECODER_INIT ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  SEQ_CONTROL ; 
 int /*<<< orphan*/  lzma2_decode ; 
 int /*<<< orphan*/  lzma2_decoder_end ; 
 TYPE_4__* lzma_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_lzma_decoder_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lzma_ret
lzma2_decoder_init(lzma_lz_decoder *lz, lzma_allocator *allocator,
		const void *opt, lzma_lz_options *lz_options)
{
	if (lz->coder == NULL) {
		lz->coder = lzma_alloc(sizeof(lzma_coder), allocator);
		if (lz->coder == NULL)
			return LZMA_MEM_ERROR;

		lz->code = &lzma2_decode;
		lz->end = &lzma2_decoder_end;

		lz->coder->lzma = LZMA_LZ_DECODER_INIT;
	}

	const lzma_options_lzma *options = opt;

	lz->coder->sequence = SEQ_CONTROL;
	lz->coder->need_properties = true;
	lz->coder->need_dictionary_reset = options->preset_dict == NULL
			|| options->preset_dict_size == 0;

	return lzma_lzma_decoder_create(&lz->coder->lzma,
			allocator, options, lz_options);
}