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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  dict_size; } ;
typedef  TYPE_1__ lzma_options_lzma ;
typedef  int /*<<< orphan*/  lzma_coder ;

/* Variables and functions */
 scalar_t__ lzma_lz_decoder_memusage (int /*<<< orphan*/ ) ; 

extern uint64_t
lzma_lzma_decoder_memusage_nocheck(const void *options)
{
	const lzma_options_lzma *const opt = options;
	return sizeof(lzma_coder) + lzma_lz_decoder_memusage(opt->dict_size);
}