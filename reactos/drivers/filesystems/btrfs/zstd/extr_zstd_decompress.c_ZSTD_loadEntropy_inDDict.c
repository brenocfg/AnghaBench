#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ZSTD_dictContentType_e ;
struct TYPE_3__ {int entropyPresent; int dictSize; char const* dictContent; int /*<<< orphan*/  entropy; void* dictID; } ;
typedef  TYPE_1__ ZSTD_DDict ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_E (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 void* MEM_readLE32 (char const*) ; 
 int ZSTD_FRAMEIDSIZE ; 
 scalar_t__ const ZSTD_MAGIC_DICTIONARY ; 
 scalar_t__ ZSTD_dct_fullDict ; 
 scalar_t__ ZSTD_dct_rawContent ; 
 int /*<<< orphan*/  ZSTD_loadEntropy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  dictionary_corrupted ; 

__attribute__((used)) static size_t
ZSTD_loadEntropy_inDDict(ZSTD_DDict* ddict,
                         ZSTD_dictContentType_e dictContentType)
{
    ddict->dictID = 0;
    ddict->entropyPresent = 0;
    if (dictContentType == ZSTD_dct_rawContent) return 0;

    if (ddict->dictSize < 8) {
        if (dictContentType == ZSTD_dct_fullDict)
            return ERROR(dictionary_corrupted);   /* only accept specified dictionaries */
        return 0;   /* pure content mode */
    }
    {   U32 const magic = MEM_readLE32(ddict->dictContent);
        if (magic != ZSTD_MAGIC_DICTIONARY) {
            if (dictContentType == ZSTD_dct_fullDict)
                return ERROR(dictionary_corrupted);   /* only accept specified dictionaries */
            return 0;   /* pure content mode */
        }
    }
    ddict->dictID = MEM_readLE32((const char*)ddict->dictContent + ZSTD_FRAMEIDSIZE);

    /* load entropy tables */
    CHECK_E( ZSTD_loadEntropy(&ddict->entropy,
                              ddict->dictContent, ddict->dictSize),
             dictionary_corrupted );
    ddict->entropyPresent = 1;
    return 0;
}