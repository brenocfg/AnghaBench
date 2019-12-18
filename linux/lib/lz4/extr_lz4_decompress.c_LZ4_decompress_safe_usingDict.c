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
 int KB ; 
 int LZ4_decompress_safe (char const*,char*,int,int) ; 
 int LZ4_decompress_safe_forceExtDict (char const*,char*,int,int,char const*,int) ; 
 int LZ4_decompress_safe_withPrefix64k (char const*,char*,int,int) ; 
 int LZ4_decompress_safe_withSmallPrefix (char const*,char*,int,int,int) ; 

int LZ4_decompress_safe_usingDict(const char *source, char *dest,
				  int compressedSize, int maxOutputSize,
				  const char *dictStart, int dictSize)
{
	if (dictSize == 0)
		return LZ4_decompress_safe(source, dest,
					   compressedSize, maxOutputSize);
	if (dictStart+dictSize == dest) {
		if (dictSize >= 64 * KB - 1)
			return LZ4_decompress_safe_withPrefix64k(source, dest,
				compressedSize, maxOutputSize);
		return LZ4_decompress_safe_withSmallPrefix(source, dest,
			compressedSize, maxOutputSize, dictSize);
	}
	return LZ4_decompress_safe_forceExtDict(source, dest,
		compressedSize, maxOutputSize, dictStart, dictSize);
}