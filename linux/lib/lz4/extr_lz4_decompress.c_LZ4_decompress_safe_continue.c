#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int prefixSize; int extDictSize; int /*<<< orphan*/ * prefixEnd; int /*<<< orphan*/ * externalDict; } ;
struct TYPE_5__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_1__ LZ4_streamDecode_t_internal ;
typedef  TYPE_2__ LZ4_streamDecode_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int KB ; 
 int LZ4_decompress_safe (char const*,char*,int,int) ; 
 int LZ4_decompress_safe_doubleDict (char const*,char*,int,int,int,int /*<<< orphan*/ *,int) ; 
 int LZ4_decompress_safe_forceExtDict (char const*,char*,int,int,int /*<<< orphan*/ *,int) ; 
 int LZ4_decompress_safe_withPrefix64k (char const*,char*,int,int) ; 
 int LZ4_decompress_safe_withSmallPrefix (char const*,char*,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 

int LZ4_decompress_safe_continue(LZ4_streamDecode_t *LZ4_streamDecode,
	const char *source, char *dest, int compressedSize, int maxOutputSize)
{
	LZ4_streamDecode_t_internal *lz4sd =
		&LZ4_streamDecode->internal_donotuse;
	int result;

	if (lz4sd->prefixSize == 0) {
		/* The first call, no dictionary yet. */
		assert(lz4sd->extDictSize == 0);
		result = LZ4_decompress_safe(source, dest,
			compressedSize, maxOutputSize);
		if (result <= 0)
			return result;
		lz4sd->prefixSize = result;
		lz4sd->prefixEnd = (BYTE *)dest + result;
	} else if (lz4sd->prefixEnd == (BYTE *)dest) {
		/* They're rolling the current segment. */
		if (lz4sd->prefixSize >= 64 * KB - 1)
			result = LZ4_decompress_safe_withPrefix64k(source, dest,
				compressedSize, maxOutputSize);
		else if (lz4sd->extDictSize == 0)
			result = LZ4_decompress_safe_withSmallPrefix(source,
				dest, compressedSize, maxOutputSize,
				lz4sd->prefixSize);
		else
			result = LZ4_decompress_safe_doubleDict(source, dest,
				compressedSize, maxOutputSize,
				lz4sd->prefixSize,
				lz4sd->externalDict, lz4sd->extDictSize);
		if (result <= 0)
			return result;
		lz4sd->prefixSize += result;
		lz4sd->prefixEnd  += result;
	} else {
		/*
		 * The buffer wraps around, or they're
		 * switching to another buffer.
		 */
		lz4sd->extDictSize = lz4sd->prefixSize;
		lz4sd->externalDict = lz4sd->prefixEnd - lz4sd->extDictSize;
		result = LZ4_decompress_safe_forceExtDict(source, dest,
			compressedSize, maxOutputSize,
			lz4sd->externalDict, lz4sd->extDictSize);
		if (result <= 0)
			return result;
		lz4sd->prefixSize = result;
		lz4sd->prefixEnd  = (BYTE *)dest + result;
	}

	return result;
}