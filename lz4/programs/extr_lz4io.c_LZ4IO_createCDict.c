#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  useDictionary; } ;
typedef  TYPE_1__ LZ4IO_prefs_t ;
typedef  int /*<<< orphan*/  LZ4F_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 int /*<<< orphan*/ * LZ4F_createCDict (void*,size_t) ; 
 void* LZ4IO_createDict (TYPE_1__* const,size_t*) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static LZ4F_CDict* LZ4IO_createCDict(LZ4IO_prefs_t* const prefs) {
    size_t dictionarySize;
    void* dictionaryBuffer;
    LZ4F_CDict* cdict;
    if (!prefs->useDictionary) {
        return NULL;
    }
    dictionaryBuffer = LZ4IO_createDict(prefs, &dictionarySize);
    if (!dictionaryBuffer) EXM_THROW(25, "Dictionary error : could not create dictionary");
    cdict = LZ4F_createCDict(dictionaryBuffer, dictionarySize);
    free(dictionaryBuffer);
    return cdict;
}