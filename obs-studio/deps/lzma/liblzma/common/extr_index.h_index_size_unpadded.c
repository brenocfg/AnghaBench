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
typedef  scalar_t__ lzma_vli ;

/* Variables and functions */
 scalar_t__ lzma_vli_size (scalar_t__) ; 

__attribute__((used)) static inline lzma_vli
index_size_unpadded(lzma_vli count, lzma_vli index_list_size)
{
	// Index Indicator + Number of Records + List of Records + CRC32
	return 1 + lzma_vli_size(count) + index_list_size + 4;
}