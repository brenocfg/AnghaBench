#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  is_lclppb_valid (void const*) ; 
 int /*<<< orphan*/  lzma_lzma_decoder_memusage_nocheck (void const*) ; 

extern uint64_t
lzma_lzma_decoder_memusage(const void *options)
{
	if (!is_lclppb_valid(options))
		return UINT64_MAX;

	return lzma_lzma_decoder_memusage_nocheck(options);
}