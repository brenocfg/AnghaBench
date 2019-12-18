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
typedef  int /*<<< orphan*/  compressFunc_t ;
typedef  scalar_t__ LZ4F_blockMode_t ;

/* Variables and functions */
 scalar_t__ LZ4F_blockIndependent ; 
 int /*<<< orphan*/  LZ4F_compressBlock ; 
 int /*<<< orphan*/  LZ4F_compressBlockHC ; 
 int /*<<< orphan*/  LZ4F_compressBlockHC_continue ; 
 int /*<<< orphan*/  LZ4F_compressBlock_continue ; 
 int LZ4HC_CLEVEL_MIN ; 

__attribute__((used)) static compressFunc_t LZ4F_selectCompression(LZ4F_blockMode_t blockMode, int level)
{
    if (level < LZ4HC_CLEVEL_MIN) {
        if (blockMode == LZ4F_blockIndependent) return LZ4F_compressBlock;
        return LZ4F_compressBlock_continue;
    }
    if (blockMode == LZ4F_blockIndependent) return LZ4F_compressBlockHC;
    return LZ4F_compressBlockHC_continue;
}