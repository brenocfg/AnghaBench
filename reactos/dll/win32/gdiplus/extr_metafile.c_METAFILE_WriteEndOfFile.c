#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ Flags; int /*<<< orphan*/  Type; } ;
struct TYPE_6__ {scalar_t__ metafile_type; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpMetafile ;
typedef  TYPE_2__ EmfPlusRecordHeader ;

/* Variables and functions */
 int /*<<< orphan*/  EmfPlusRecordTypeEndOfFile ; 
 int /*<<< orphan*/  METAFILE_AllocateRecord (TYPE_1__*,int,void**) ; 
 int /*<<< orphan*/  METAFILE_WriteRecords (TYPE_1__*) ; 
 scalar_t__ MetafileTypeEmfPlusDual ; 
 scalar_t__ MetafileTypeEmfPlusOnly ; 
 int /*<<< orphan*/  Ok ; 

__attribute__((used)) static GpStatus METAFILE_WriteEndOfFile(GpMetafile *metafile)
{
    GpStatus stat;

    if (metafile->metafile_type == MetafileTypeEmfPlusOnly || metafile->metafile_type == MetafileTypeEmfPlusDual)
    {
        EmfPlusRecordHeader *record;

        stat = METAFILE_AllocateRecord(metafile, sizeof(EmfPlusRecordHeader), (void**)&record);
        if (stat != Ok)
            return stat;

        record->Type = EmfPlusRecordTypeEndOfFile;
        record->Flags = 0;

        METAFILE_WriteRecords(metafile);
    }

    return Ok;
}