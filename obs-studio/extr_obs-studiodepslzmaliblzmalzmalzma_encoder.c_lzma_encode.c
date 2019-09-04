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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_4__ {scalar_t__ action; } ;
typedef  TYPE_1__ lzma_mf ;
typedef  int /*<<< orphan*/  lzma_coder ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 scalar_t__ LZMA_SYNC_FLUSH ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  lzma_lzma_encode (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static lzma_ret
lzma_encode(lzma_coder *restrict coder, lzma_mf *restrict mf,
		uint8_t *restrict out, size_t *restrict out_pos,
		size_t out_size)
{
	// Plain LZMA has no support for sync-flushing.
	if (unlikely(mf->action == LZMA_SYNC_FLUSH))
		return LZMA_OPTIONS_ERROR;

	return lzma_lzma_encode(coder, mf, out, out_pos, out_size, UINT32_MAX);
}