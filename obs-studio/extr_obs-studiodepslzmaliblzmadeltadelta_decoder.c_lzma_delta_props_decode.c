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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_3__ {scalar_t__ dist; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ lzma_options_delta ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_DELTA_TYPE_BYTE ; 
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 TYPE_1__* lzma_alloc (int,int /*<<< orphan*/ *) ; 

extern lzma_ret
lzma_delta_props_decode(void **options, lzma_allocator *allocator,
		const uint8_t *props, size_t props_size)
{
	if (props_size != 1)
		return LZMA_OPTIONS_ERROR;

	lzma_options_delta *opt
			= lzma_alloc(sizeof(lzma_options_delta), allocator);
	if (opt == NULL)
		return LZMA_MEM_ERROR;

	opt->type = LZMA_DELTA_TYPE_BYTE;
	opt->dist = props[0] + 1;

	*options = opt;

	return LZMA_OK;
}