#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_2__ {scalar_t__ start_offset; } ;
typedef  TYPE_1__ lzma_options_bcj ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_OK ; 

extern lzma_ret
lzma_simple_props_size(uint32_t *size, const void *options)
{
	const lzma_options_bcj *const opt = options;
	*size = (opt == NULL || opt->start_offset == 0) ? 0 : 4;
	return LZMA_OK;
}