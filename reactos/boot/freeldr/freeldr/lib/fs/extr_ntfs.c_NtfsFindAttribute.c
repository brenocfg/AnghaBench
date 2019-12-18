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
typedef  scalar_t__ WCHAR ;
typedef  size_t ULONG ;
struct TYPE_7__ {scalar_t__ AttributesOffset; } ;
struct TYPE_6__ {scalar_t__ MftRecordSize; } ;
typedef  TYPE_1__* PNTFS_VOLUME_INFO ;
typedef  TYPE_2__* PNTFS_MFT_RECORD ;
typedef  scalar_t__ PNTFS_ATTR_RECORD ;
typedef  int /*<<< orphan*/  PNTFS_ATTR_CONTEXT ;
typedef  scalar_t__ PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  NtfsFindAttributeHelper (TYPE_1__*,scalar_t__,scalar_t__,size_t,scalar_t__ const*,size_t) ; 

__attribute__((used)) static PNTFS_ATTR_CONTEXT NtfsFindAttribute(PNTFS_VOLUME_INFO Volume, PNTFS_MFT_RECORD MftRecord, ULONG Type, const WCHAR *Name)
{
    PNTFS_ATTR_RECORD AttrRecord;
    PNTFS_ATTR_RECORD AttrRecordEnd;
    ULONG NameLength;

    AttrRecord = (PNTFS_ATTR_RECORD)((PCHAR)MftRecord + MftRecord->AttributesOffset);
    AttrRecordEnd = (PNTFS_ATTR_RECORD)((PCHAR)MftRecord + Volume->MftRecordSize);
    for (NameLength = 0; Name[NameLength] != 0; NameLength++)
        ;

    return NtfsFindAttributeHelper(Volume, AttrRecord, AttrRecordEnd, Type, Name, NameLength);
}