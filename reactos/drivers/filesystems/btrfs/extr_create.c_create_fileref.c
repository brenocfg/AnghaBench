#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int refcount; TYPE_9__* nonpaged; int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ file_ref ;
struct TYPE_11__ {int /*<<< orphan*/  fileref_lookaside; int /*<<< orphan*/  fileref_np_lookaside; } ;
typedef  TYPE_2__ device_extension ;
struct TYPE_12__ {int /*<<< orphan*/  fileref_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_9__* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 TYPE_1__* ExAllocateFromPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreeToPagedLookasideList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ExInitializeResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  WARN (char*,TYPE_1__*) ; 

file_ref* create_fileref(device_extension* Vcb) {
    file_ref* fr;

    fr = ExAllocateFromPagedLookasideList(&Vcb->fileref_lookaside);
    if (!fr) {
        ERR("out of memory\n");
        return NULL;
    }

    RtlZeroMemory(fr, sizeof(file_ref));

    fr->nonpaged = ExAllocateFromNPagedLookasideList(&Vcb->fileref_np_lookaside);
    if (!fr->nonpaged) {
        ERR("out of memory\n");
        ExFreeToPagedLookasideList(&Vcb->fileref_lookaside, fr);
        return NULL;
    }

    fr->refcount = 1;

#ifdef DEBUG_FCB_REFCOUNTS
    WARN("fileref %p: refcount now 1\n", fr);
#endif

    InitializeListHead(&fr->children);

    ExInitializeResourceLite(&fr->nonpaged->fileref_lock);

    return fr;
}