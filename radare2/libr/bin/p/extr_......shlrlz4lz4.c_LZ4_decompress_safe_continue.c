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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {int prefixSize; int extDictSize; int /*<<< orphan*/ * prefixEnd; int /*<<< orphan*/ * externalDict; } ;
struct TYPE_5__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_1__ LZ4_streamDecode_t_internal ;
typedef  TYPE_2__ LZ4_streamDecode_t ;

/* Variables and functions */
 int LZ4_decompress_generic (char const*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  endOnInputSize ; 
 int /*<<< orphan*/  full ; 
 int /*<<< orphan*/  usingExtDict ; 

int LZ4_decompress_safe_continue (LZ4_streamDecode_t* LZ4_streamDecode, const char* source, char* dest, int compressedSize, int maxOutputSize) {
	LZ4_streamDecode_t_internal* lz4sd = &LZ4_streamDecode->internal_donotuse;
	int result;

	if (lz4sd->prefixEnd == (ut8*)dest) {
		result = LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize,
				endOnInputSize, full, 0,
				usingExtDict, lz4sd->prefixEnd - lz4sd->prefixSize, lz4sd->externalDict, lz4sd->extDictSize);
		if (result <= 0) return result;
		lz4sd->prefixSize += result;
		lz4sd->prefixEnd  += result;
	} else {
		lz4sd->extDictSize = lz4sd->prefixSize;
		lz4sd->externalDict = lz4sd->prefixEnd - lz4sd->extDictSize;
		result = LZ4_decompress_generic(source, dest, compressedSize, maxOutputSize,
				endOnInputSize, full, 0,
				usingExtDict, (ut8*)dest, lz4sd->externalDict, lz4sd->extDictSize);
		if (result <= 0) return result;
		lz4sd->prefixSize = result;
		lz4sd->prefixEnd  = (ut8*)dest + result;
	}

	return result;
}