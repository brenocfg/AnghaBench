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
typedef  int /*<<< orphan*/  mfName ;
typedef  int U64 ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_benchCLevel (void*,size_t,char const*,int,int,size_t*,unsigned int,char const*,int) ; 
 int BMK_findMaxMem (int const) ; 
 int /*<<< orphan*/  BMK_loadFiles (void*,size_t,size_t*,char const**,unsigned int) ; 
 int /*<<< orphan*/  DISPLAY (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 size_t LZ4_MAX_INPUT_SIZE ; 
 int UTIL_getTotalFileSize (char const**,unsigned int) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static void BMK_benchFileTable(const char** fileNamesTable, unsigned nbFiles,
                               int cLevel, int cLevelLast,
                               const char* dictBuf, int dictSize)
{
    void* srcBuffer;
    size_t benchedSize;
    size_t* fileSizes = (size_t*)malloc(nbFiles * sizeof(size_t));
    U64 const totalSizeToLoad = UTIL_getTotalFileSize(fileNamesTable, nbFiles);
    char mfName[20] = {0};

    if (!fileSizes) EXM_THROW(12, "not enough memory for fileSizes");

    /* Memory allocation & restrictions */
    benchedSize = BMK_findMaxMem(totalSizeToLoad * 3) / 3;
    if (benchedSize==0) EXM_THROW(12, "not enough memory");
    if ((U64)benchedSize > totalSizeToLoad) benchedSize = (size_t)totalSizeToLoad;
    if (benchedSize > LZ4_MAX_INPUT_SIZE) {
        benchedSize = LZ4_MAX_INPUT_SIZE;
        DISPLAY("File(s) bigger than LZ4's max input size; testing %u MB only...\n", (U32)(benchedSize >> 20));
    } else {
        if (benchedSize < totalSizeToLoad)
            DISPLAY("Not enough memory; testing %u MB only...\n", (U32)(benchedSize >> 20));
    }
    srcBuffer = malloc(benchedSize + !benchedSize);   /* avoid alloc of zero */
    if (!srcBuffer) EXM_THROW(12, "not enough memory");

    /* Load input buffer */
    BMK_loadFiles(srcBuffer, benchedSize, fileSizes, fileNamesTable, nbFiles);

    /* Bench */
    snprintf (mfName, sizeof(mfName), " %u files", nbFiles);
    {   const char* displayName = (nbFiles > 1) ? mfName : fileNamesTable[0];
        BMK_benchCLevel(srcBuffer, benchedSize,
                        displayName, cLevel, cLevelLast,
                        fileSizes, nbFiles,
                        dictBuf, dictSize);
    }

    /* clean up */
    free(srcBuffer);
    free(fileSizes);
}