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
typedef  int /*<<< orphan*/  cRess_t ;
typedef  int /*<<< orphan*/  LZ4IO_prefs_t ;

/* Variables and functions */
 size_t FNSPACE ; 
 scalar_t__ LZ4IO_compressFilename_extRess (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,char const*,char*,int) ; 
 int /*<<< orphan*/  LZ4IO_createCResources (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  LZ4IO_freeCResources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 char* stdoutmark ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

int LZ4IO_compressMultipleFilenames(LZ4IO_prefs_t* const prefs,
                              const char** inFileNamesTable, int ifntSize,
                              const char* suffix,
                              int compressionLevel)
{
    int i;
    int missed_files = 0;
    char* dstFileName = (char*)malloc(FNSPACE);
    size_t ofnSize = FNSPACE;
    const size_t suffixSize = strlen(suffix);
    cRess_t ress;

    if (dstFileName == NULL) return ifntSize;   /* not enough memory */
    ress = LZ4IO_createCResources(prefs);

    /* loop on each file */
    for (i=0; i<ifntSize; i++) {
        size_t const ifnSize = strlen(inFileNamesTable[i]);
        if (!strcmp(suffix, stdoutmark)) {
            missed_files += LZ4IO_compressFilename_extRess(prefs, ress,
                                    inFileNamesTable[i], stdoutmark,
                                    compressionLevel);
            continue;
        }
        if (ofnSize <= ifnSize+suffixSize+1) {
            free(dstFileName);
            ofnSize = ifnSize + 20;
            dstFileName = (char*)malloc(ofnSize);
            if (dstFileName==NULL) {
                LZ4IO_freeCResources(ress);
                return ifntSize;
        }   }
        strcpy(dstFileName, inFileNamesTable[i]);
        strcat(dstFileName, suffix);

        missed_files += LZ4IO_compressFilename_extRess(prefs, ress,
                                inFileNamesTable[i], dstFileName,
                                compressionLevel);
    }

    /* Close & Free */
    LZ4IO_freeCResources(ress);
    free(dstFileName);

    return missed_files;
}