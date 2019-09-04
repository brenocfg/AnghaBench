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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sizes ;
typedef  scalar_t__ const lzma_vli ;
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_3__ {int /*<<< orphan*/  check; int /*<<< orphan*/  count; int /*<<< orphan*/  index_list_size; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/  blocks_size; } ;
typedef  TYPE_1__ lzma_index_hash_info ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_CHECK_BEST ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  lzma_check_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ lzma_vli_size (scalar_t__ const) ; 
 scalar_t__ vli_ceil4 (scalar_t__ const) ; 

__attribute__((used)) static lzma_ret
hash_append(lzma_index_hash_info *info, lzma_vli unpadded_size,
		lzma_vli uncompressed_size)
{
	info->blocks_size += vli_ceil4(unpadded_size);
	info->uncompressed_size += uncompressed_size;
	info->index_list_size += lzma_vli_size(unpadded_size)
			+ lzma_vli_size(uncompressed_size);
	++info->count;

	const lzma_vli sizes[2] = { unpadded_size, uncompressed_size };
	lzma_check_update(&info->check, LZMA_CHECK_BEST,
			(const uint8_t *)(sizes), sizeof(sizes));

	return LZMA_OK;
}