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
typedef  int /*<<< orphan*/  const ut8 ;
typedef  int ut32 ;
struct TYPE_6__ {int dictSize; int /*<<< orphan*/  currentOffset; int /*<<< orphan*/  const* dictionary; } ;
struct TYPE_7__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_1__ LZ4_stream_t_internal ;
typedef  TYPE_2__ LZ4_stream_t ;

/* Variables and functions */
 int LZ4_compress_generic (TYPE_1__*,char const*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LZ4_renormDictT (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  byut32 ; 
 int /*<<< orphan*/  noDictIssue ; 
 int /*<<< orphan*/  notLimited ; 
 int /*<<< orphan*/  usingExtDict ; 

int LZ4_compress_forceExtDict (LZ4_stream_t* LZ4_dict, const char* source, char* dest, int inputSize) {
	LZ4_stream_t_internal* streamPtr = &LZ4_dict->internal_donotuse;
	int result;
	const ut8* const dictEnd = streamPtr->dictionary + streamPtr->dictSize;

	const ut8* smallest = dictEnd;
	if (smallest > (const ut8*) source) smallest = (const ut8*) source;
	LZ4_renormDictT(streamPtr, smallest);

	result = LZ4_compress_generic(streamPtr, source, dest, inputSize, 0, notLimited, byut32, usingExtDict, noDictIssue, 1);

	streamPtr->dictionary = (const ut8*)source;
	streamPtr->dictSize = (ut32)inputSize;
	streamPtr->currentOffset += (ut32)inputSize;

	return result;
}