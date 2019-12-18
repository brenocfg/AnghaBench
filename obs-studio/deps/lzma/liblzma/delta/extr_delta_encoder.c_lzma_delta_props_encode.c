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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_2__ {scalar_t__ dist; } ;
typedef  TYPE_1__ lzma_options_delta ;

/* Variables and functions */
 scalar_t__ LZMA_DELTA_DIST_MIN ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 scalar_t__ UINT64_MAX ; 
 scalar_t__ lzma_delta_coder_memusage (void const*) ; 

extern lzma_ret
lzma_delta_props_encode(const void *options, uint8_t *out)
{
	// The caller must have already validated the options, so it's
	// LZMA_PROG_ERROR if they are invalid.
	if (lzma_delta_coder_memusage(options) == UINT64_MAX)
		return LZMA_PROG_ERROR;

	const lzma_options_delta *opt = options;
	out[0] = opt->dist - LZMA_DELTA_DIST_MIN;

	return LZMA_OK;
}