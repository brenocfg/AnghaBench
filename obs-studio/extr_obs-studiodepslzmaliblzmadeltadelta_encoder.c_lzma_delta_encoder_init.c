#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_4__ {int /*<<< orphan*/ * update; int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ lzma_next_coder ;
typedef  int /*<<< orphan*/  lzma_filter_info ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  delta_encode ; 
 int /*<<< orphan*/  delta_encoder_update ; 
 int /*<<< orphan*/  lzma_delta_coder_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

extern lzma_ret
lzma_delta_encoder_init(lzma_next_coder *next, lzma_allocator *allocator,
		const lzma_filter_info *filters)
{
	next->code = &delta_encode;
	next->update = &delta_encoder_update;
	return lzma_delta_coder_init(next, allocator, filters);
}