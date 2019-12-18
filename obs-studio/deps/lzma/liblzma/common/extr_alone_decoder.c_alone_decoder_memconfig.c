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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_3__ {scalar_t__ memusage; scalar_t__ memlimit; } ;
typedef  TYPE_1__ lzma_coder ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEMLIMIT_ERROR ; 
 int /*<<< orphan*/  LZMA_OK ; 

__attribute__((used)) static lzma_ret
alone_decoder_memconfig(lzma_coder *coder, uint64_t *memusage,
		uint64_t *old_memlimit, uint64_t new_memlimit)
{
	*memusage = coder->memusage;
	*old_memlimit = coder->memlimit;

	if (new_memlimit != 0) {
		if (new_memlimit < coder->memusage)
			return LZMA_MEMLIMIT_ERROR;

		coder->memlimit = new_memlimit;
	}

	return LZMA_OK;
}