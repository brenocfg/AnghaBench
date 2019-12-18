#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ Buffer; } ;
struct TYPE_19__ {scalar_t__ Flink; } ;
struct TYPE_16__ {TYPE_3__ oldutf8; TYPE_8__* fcb; scalar_t__ parent; TYPE_9__ list_entry; TYPE_2__* dc; TYPE_11__* nonpaged; } ;
typedef  TYPE_4__ file_ref ;
struct TYPE_17__ {int /*<<< orphan*/  fileref_lookaside; int /*<<< orphan*/  fileref_np_lookaside; } ;
typedef  TYPE_5__ device_extension ;
struct TYPE_13__ {int /*<<< orphan*/  Length; } ;
struct TYPE_18__ {TYPE_1__ adsdata; scalar_t__ ads; TYPE_4__* fileref; } ;
struct TYPE_14__ {int /*<<< orphan*/ * fileref; int /*<<< orphan*/  size; } ;
struct TYPE_12__ {int /*<<< orphan*/  fileref_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ExDeleteResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreePool (scalar_t__) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  ExFreeToPagedLookasideList (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  RemoveEntryList (TYPE_9__*) ; 
 int /*<<< orphan*/  free_fcb (TYPE_8__*) ; 
 int /*<<< orphan*/  free_fileref (scalar_t__) ; 

void reap_fileref(device_extension* Vcb, file_ref* fr) {
    // FIXME - do we need a file_ref lock?

    // FIXME - do delete if needed

    ExDeleteResourceLite(&fr->nonpaged->fileref_lock);

    ExFreeToNPagedLookasideList(&Vcb->fileref_np_lookaside, fr->nonpaged);

    // FIXME - throw error if children not empty

    if (fr->fcb->fileref == fr)
        fr->fcb->fileref = NULL;

    if (fr->dc) {
        if (fr->fcb->ads)
            fr->dc->size = fr->fcb->adsdata.Length;

        fr->dc->fileref = NULL;
    }

    if (fr->list_entry.Flink)
        RemoveEntryList(&fr->list_entry);

    if (fr->parent)
        free_fileref(fr->parent);

    free_fcb(fr->fcb);

    if (fr->oldutf8.Buffer)
        ExFreePool(fr->oldutf8.Buffer);

    ExFreeToPagedLookasideList(&Vcb->fileref_lookaside, fr);
}