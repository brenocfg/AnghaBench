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
struct TYPE_3__ {int /*<<< orphan*/  writeflags; int /*<<< orphan*/  readflags; int /*<<< orphan*/ * innerloopsizeptr; int /*<<< orphan*/ * innerstrides; int /*<<< orphan*/  operands; int /*<<< orphan*/  dtypes; int /*<<< orphan*/  dataptrs; int /*<<< orphan*/ * get_multi_index; int /*<<< orphan*/ * iternext; int /*<<< orphan*/ * iter; } ;
typedef  int /*<<< orphan*/  NpyIter ;
typedef  TYPE_1__ NewNpyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  NpyIter_GetDataPtrArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NpyIter_GetDescrArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NpyIter_GetGetMultiIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NpyIter_GetInnerLoopSizePtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NpyIter_GetInnerStrideArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NpyIter_GetIterNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NpyIter_GetOperandArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NpyIter_GetReadFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NpyIter_GetWriteFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NpyIter_HasDelayedBufAlloc (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_HasExternalLoop (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyIter_HasMultiIndex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int npyiter_cache_values(NewNpyArrayIterObject *self)
{
    NpyIter *iter = self->iter;

    /* iternext and get_multi_index functions */
    self->iternext = NpyIter_GetIterNext(iter, NULL);
    if (self->iternext == NULL) {
        return -1;
    }

    if (NpyIter_HasMultiIndex(iter) && !NpyIter_HasDelayedBufAlloc(iter)) {
        self->get_multi_index = NpyIter_GetGetMultiIndex(iter, NULL);
    }
    else {
        self->get_multi_index = NULL;
    }

    /* Internal data pointers */
    self->dataptrs = NpyIter_GetDataPtrArray(iter);
    self->dtypes = NpyIter_GetDescrArray(iter);
    self->operands = NpyIter_GetOperandArray(iter);

    if (NpyIter_HasExternalLoop(iter)) {
        self->innerstrides = NpyIter_GetInnerStrideArray(iter);
        self->innerloopsizeptr = NpyIter_GetInnerLoopSizePtr(iter);
    }
    else {
        self->innerstrides = NULL;
        self->innerloopsizeptr = NULL;
    }

    /* The read/write settings */
    NpyIter_GetReadFlags(iter, self->readflags);
    NpyIter_GetWriteFlags(iter, self->writeflags);
    return 0;
}