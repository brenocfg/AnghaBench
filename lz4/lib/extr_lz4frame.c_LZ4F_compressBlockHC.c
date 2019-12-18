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
typedef  int /*<<< orphan*/  LZ4F_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4F_blockIndependent ; 
 int /*<<< orphan*/  LZ4F_initStream (void*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int LZ4_compress_HC_continue (int /*<<< orphan*/ *,char const*,char*,int,int) ; 
 int LZ4_compress_HC_extStateHC_fastReset (void*,char const*,char*,int,int,int) ; 

__attribute__((used)) static int LZ4F_compressBlockHC(void* ctx, const char* src, char* dst, int srcSize, int dstCapacity, int level, const LZ4F_CDict* cdict)
{
    LZ4F_initStream(ctx, cdict, level, LZ4F_blockIndependent);
    if (cdict) {
        return LZ4_compress_HC_continue((LZ4_streamHC_t*)ctx, src, dst, srcSize, dstCapacity);
    }
    return LZ4_compress_HC_extStateHC_fastReset(ctx, src, dst, srcSize, dstCapacity, level);
}