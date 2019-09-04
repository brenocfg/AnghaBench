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
typedef  int U32 ;

/* Variables and functions */
 int const ZSTD_MAGICNUMBER ; 
 int const ZSTD_MAGIC_SKIPPABLE_START ; 
 int ZSTD_readLE32 (void const*) ; 

unsigned ZSTD_isFrame(const void *buffer, size_t size)
{
	if (size < 4)
		return 0;
	{
		U32 const magic = ZSTD_readLE32(buffer);
		if (magic == ZSTD_MAGICNUMBER)
			return 1;
		if ((magic & 0xFFFFFFF0U) == ZSTD_MAGIC_SKIPPABLE_START)
			return 1;
	}
	return 0;
}