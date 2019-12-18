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
typedef  int /*<<< orphan*/  ZSTD_matchState_t ;
typedef  int /*<<< orphan*/  ZSTD_dictTableLoadMethod_e ;
typedef  scalar_t__ ZSTD_dictContentType_e ;
typedef  int /*<<< orphan*/  ZSTD_compressedBlockState_t ;
typedef  int /*<<< orphan*/  ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_readLE32 (void const*) ; 
 scalar_t__ ZSTD_MAGIC_DICTIONARY ; 
 scalar_t__ ZSTD_dct_auto ; 
 scalar_t__ ZSTD_dct_fullDict ; 
 scalar_t__ ZSTD_dct_rawContent ; 
 size_t ZSTD_loadDictionaryContent (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t,int /*<<< orphan*/ ) ; 
 size_t ZSTD_loadZstdDictionary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ZSTD_reset_compressedBlockState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_wrong ; 

__attribute__((used)) static size_t
ZSTD_compress_insertDictionary(ZSTD_compressedBlockState_t* bs,
                               ZSTD_matchState_t* ms,
                         const ZSTD_CCtx_params* params,
                         const void* dict, size_t dictSize,
                               ZSTD_dictContentType_e dictContentType,
                               ZSTD_dictTableLoadMethod_e dtlm,
                               void* workspace)
{
    DEBUGLOG(4, "ZSTD_compress_insertDictionary (dictSize=%u)", (U32)dictSize);
    if ((dict==NULL) || (dictSize<=8)) return 0;

    ZSTD_reset_compressedBlockState(bs);

    /* dict restricted modes */
    if (dictContentType == ZSTD_dct_rawContent)
        return ZSTD_loadDictionaryContent(ms, params, dict, dictSize, dtlm);

    if (MEM_readLE32(dict) != ZSTD_MAGIC_DICTIONARY) {
        if (dictContentType == ZSTD_dct_auto) {
            DEBUGLOG(4, "raw content dictionary detected");
            return ZSTD_loadDictionaryContent(ms, params, dict, dictSize, dtlm);
        }
        if (dictContentType == ZSTD_dct_fullDict)
            return ERROR(dictionary_wrong);
        assert(0);   /* impossible */
    }

    /* dict as full zstd dictionary */
    return ZSTD_loadZstdDictionary(bs, ms, params, dict, dictSize, dtlm, workspace);
}