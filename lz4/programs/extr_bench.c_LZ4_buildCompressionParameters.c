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
struct compressionParameters {int cLevel; char const* dictBuf; int dictSize; int /*<<< orphan*/  blockFunction; int /*<<< orphan*/  cleanupFunction; int /*<<< orphan*/  resetFunction; int /*<<< orphan*/  initFunction; } ;

/* Variables and functions */
 int LZ4HC_CLEVEL_MIN ; 
 int /*<<< orphan*/  LZ4_compressBlockNoStream ; 
 int /*<<< orphan*/  LZ4_compressBlockNoStreamHC ; 
 int /*<<< orphan*/  LZ4_compressBlockStream ; 
 int /*<<< orphan*/  LZ4_compressBlockStreamHC ; 
 int /*<<< orphan*/  LZ4_compressCleanupNoStream ; 
 int /*<<< orphan*/  LZ4_compressCleanupStream ; 
 int /*<<< orphan*/  LZ4_compressCleanupStreamHC ; 
 int /*<<< orphan*/  LZ4_compressInitNoStream ; 
 int /*<<< orphan*/  LZ4_compressInitStream ; 
 int /*<<< orphan*/  LZ4_compressInitStreamHC ; 
 int /*<<< orphan*/  LZ4_compressResetNoStream ; 
 int /*<<< orphan*/  LZ4_compressResetStream ; 
 int /*<<< orphan*/  LZ4_compressResetStreamHC ; 

__attribute__((used)) static void LZ4_buildCompressionParameters(
    struct compressionParameters* pParams,
    int cLevel, const char* dictBuf, int dictSize)
{
    pParams->cLevel = cLevel;
    pParams->dictBuf = dictBuf;
    pParams->dictSize = dictSize;

    if (dictSize) {
        if (cLevel < LZ4HC_CLEVEL_MIN) {
            pParams->initFunction = LZ4_compressInitStream;
            pParams->resetFunction = LZ4_compressResetStream;
            pParams->blockFunction = LZ4_compressBlockStream;
            pParams->cleanupFunction = LZ4_compressCleanupStream;
        } else {
            pParams->initFunction = LZ4_compressInitStreamHC;
            pParams->resetFunction = LZ4_compressResetStreamHC;
            pParams->blockFunction = LZ4_compressBlockStreamHC;
            pParams->cleanupFunction = LZ4_compressCleanupStreamHC;
        }
    } else {
        pParams->initFunction = LZ4_compressInitNoStream;
        pParams->resetFunction = LZ4_compressResetNoStream;
        pParams->cleanupFunction = LZ4_compressCleanupNoStream;

        if (cLevel < LZ4HC_CLEVEL_MIN) {
            pParams->blockFunction = LZ4_compressBlockNoStream;
        } else {
            pParams->blockFunction = LZ4_compressBlockNoStreamHC;
        }
    }
}