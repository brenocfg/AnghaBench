#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* U32 ;
struct TYPE_6__ {int dictSize; int currentOffset; int /*<<< orphan*/  const* dictionary; scalar_t__ initCheck; } ;
struct TYPE_7__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_1__ LZ4_stream_t_internal ;
typedef  TYPE_2__ LZ4_stream_t ;
typedef  int /*<<< orphan*/  const BYTE ;

/* Variables and functions */
 int KB ; 
 int LZ4_ACCELERATION_DEFAULT ; 
 int LZ4_compress_generic (TYPE_1__*,char const*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LZ4_renormDictT (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  byU32 ; 
 int /*<<< orphan*/  dictSmall ; 
 int /*<<< orphan*/  limitedOutput ; 
 int /*<<< orphan*/  noDictIssue ; 
 int /*<<< orphan*/  usingExtDict ; 
 int /*<<< orphan*/  withPrefix64k ; 

int LZ4_compress_fast_continue(LZ4_stream_t *LZ4_stream, const char *source,
	char *dest, int inputSize, int maxOutputSize, int acceleration)
{
	LZ4_stream_t_internal *streamPtr = &LZ4_stream->internal_donotuse;
	const BYTE * const dictEnd = streamPtr->dictionary
		+ streamPtr->dictSize;

	const BYTE *smallest = (const BYTE *) source;

	if (streamPtr->initCheck) {
		/* Uninitialized structure detected */
		return 0;
	}

	if ((streamPtr->dictSize > 0) && (smallest > dictEnd))
		smallest = dictEnd;

	LZ4_renormDictT(streamPtr, smallest);

	if (acceleration < 1)
		acceleration = LZ4_ACCELERATION_DEFAULT;

	/* Check overlapping input/dictionary space */
	{
		const BYTE *sourceEnd = (const BYTE *) source + inputSize;

		if ((sourceEnd > streamPtr->dictionary)
			&& (sourceEnd < dictEnd)) {
			streamPtr->dictSize = (U32)(dictEnd - sourceEnd);
			if (streamPtr->dictSize > 64 * KB)
				streamPtr->dictSize = 64 * KB;
			if (streamPtr->dictSize < 4)
				streamPtr->dictSize = 0;
			streamPtr->dictionary = dictEnd - streamPtr->dictSize;
		}
	}

	/* prefix mode : source data follows dictionary */
	if (dictEnd == (const BYTE *)source) {
		int result;

		if ((streamPtr->dictSize < 64 * KB) &&
			(streamPtr->dictSize < streamPtr->currentOffset)) {
			result = LZ4_compress_generic(
				streamPtr, source, dest, inputSize,
				maxOutputSize, limitedOutput, byU32,
				withPrefix64k, dictSmall, acceleration);
		} else {
			result = LZ4_compress_generic(
				streamPtr, source, dest, inputSize,
				maxOutputSize, limitedOutput, byU32,
				withPrefix64k, noDictIssue, acceleration);
		}
		streamPtr->dictSize += (U32)inputSize;
		streamPtr->currentOffset += (U32)inputSize;
		return result;
	}

	/* external dictionary mode */
	{
		int result;

		if ((streamPtr->dictSize < 64 * KB) &&
			(streamPtr->dictSize < streamPtr->currentOffset)) {
			result = LZ4_compress_generic(
				streamPtr, source, dest, inputSize,
				maxOutputSize, limitedOutput, byU32,
				usingExtDict, dictSmall, acceleration);
		} else {
			result = LZ4_compress_generic(
				streamPtr, source, dest, inputSize,
				maxOutputSize, limitedOutput, byU32,
				usingExtDict, noDictIssue, acceleration);
		}
		streamPtr->dictionary = (const BYTE *)source;
		streamPtr->dictSize = (U32)inputSize;
		streamPtr->currentOffset += (U32)inputSize;
		return result;
	}
}