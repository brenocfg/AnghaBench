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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_3__ {int dict_size; scalar_t__ preset_dict_size; int /*<<< orphan*/ * preset_dict; } ;
typedef  TYPE_1__ lzma_options_lzma ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int UINT32_MAX ; 
 TYPE_1__* lzma_alloc (int,int /*<<< orphan*/ *) ; 

extern lzma_ret
lzma_lzma2_props_decode(void **options, lzma_allocator *allocator,
		const uint8_t *props, size_t props_size)
{
	if (props_size != 1)
		return LZMA_OPTIONS_ERROR;

	// Check that reserved bits are unset.
	if (props[0] & 0xC0)
		return LZMA_OPTIONS_ERROR;

	// Decode the dictionary size.
	if (props[0] > 40)
		return LZMA_OPTIONS_ERROR;

	lzma_options_lzma *opt = lzma_alloc(
			sizeof(lzma_options_lzma), allocator);
	if (opt == NULL)
		return LZMA_MEM_ERROR;

	if (props[0] == 40) {
		opt->dict_size = UINT32_MAX;
	} else {
		opt->dict_size = 2 | (props[0] & 1);
		opt->dict_size <<= props[0] / 2 + 11;
	}

	opt->preset_dict = NULL;
	opt->preset_dict_size = 0;

	*options = opt;

	return LZMA_OK;
}