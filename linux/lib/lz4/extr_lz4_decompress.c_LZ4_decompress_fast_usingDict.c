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
 int LZ4_decompress_fast (char const*,char*,int) ; 
 int LZ4_decompress_fast_extDict (char const*,char*,int,char const*,int) ; 

int LZ4_decompress_fast_usingDict(const char *source, char *dest,
				  int originalSize,
				  const char *dictStart, int dictSize)
{
	if (dictSize == 0 || dictStart + dictSize == dest)
		return LZ4_decompress_fast(source, dest, originalSize);

	return LZ4_decompress_fast_extDict(source, dest, originalSize,
		dictStart, dictSize);
}