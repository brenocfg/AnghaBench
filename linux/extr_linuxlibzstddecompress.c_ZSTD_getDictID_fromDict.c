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

/* Variables and functions */
 scalar_t__ ZSTD_DICT_MAGIC ; 
 int ZSTD_readLE32 (char const*) ; 

unsigned ZSTD_getDictID_fromDict(const void *dict, size_t dictSize)
{
	if (dictSize < 8)
		return 0;
	if (ZSTD_readLE32(dict) != ZSTD_DICT_MAGIC)
		return 0;
	return ZSTD_readLE32((const char *)dict + 4);
}