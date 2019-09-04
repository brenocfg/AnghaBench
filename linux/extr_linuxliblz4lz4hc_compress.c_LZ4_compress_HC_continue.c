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
typedef  int /*<<< orphan*/  LZ4_streamHC_t ;

/* Variables and functions */
 int LZ4_compressBound (int) ; 
 int LZ4_compressHC_continue_generic (int /*<<< orphan*/ *,char const*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  limitedOutput ; 
 int /*<<< orphan*/  noLimit ; 

int LZ4_compress_HC_continue(
	LZ4_streamHC_t *LZ4_streamHCPtr,
	const char *source,
	char *dest,
	int inputSize,
	int maxOutputSize)
{
	if (maxOutputSize < LZ4_compressBound(inputSize))
		return LZ4_compressHC_continue_generic(LZ4_streamHCPtr,
			source, dest, inputSize, maxOutputSize, limitedOutput);
	else
		return LZ4_compressHC_continue_generic(LZ4_streamHCPtr,
			source, dest, inputSize, maxOutputSize, noLimit);
}