#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  internal_donotuse; } ;
typedef  TYPE_1__ LZ4_stream_t ;

/* Variables and functions */
 int LZ4_64Klimit ; 
 int LZ4_compressBound (int) ; 
 int LZ4_compress_destSize_generic (int /*<<< orphan*/ *,char const*,char*,int*,int,int /*<<< orphan*/ ) ; 
 int LZ4_compress_fast_extState (TYPE_1__*,char const*,char*,int,int,int) ; 
 int /*<<< orphan*/  LZ4_resetStream (TYPE_1__*) ; 
 int /*<<< orphan*/  byPtr ; 
 int /*<<< orphan*/  byut16 ; 
 int /*<<< orphan*/  byut32 ; 

__attribute__((used)) static int LZ4_compress_destSize_extState (LZ4_stream_t* state, const char* src, char* dst, int* srcSizePtr, int targetDstSize) {
	LZ4_resetStream (state);
	if (targetDstSize >= LZ4_compressBound(*srcSizePtr)) {  /* compression success is guaranteed */
		return LZ4_compress_fast_extState(state, src, dst, *srcSizePtr, targetDstSize, 1);
	}
	if (*srcSizePtr < LZ4_64Klimit) {
		return LZ4_compress_destSize_generic(&state->internal_donotuse, src, dst, srcSizePtr, targetDstSize, byut16);
	}
	return LZ4_compress_destSize_generic(&state->internal_donotuse, src, dst, srcSizePtr, targetDstSize, sizeof(void*)==8 ? byut32 : byPtr);
}