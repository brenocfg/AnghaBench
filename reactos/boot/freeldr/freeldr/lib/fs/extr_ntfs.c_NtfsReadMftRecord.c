#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
struct TYPE_5__ {int MftRecordSize; int /*<<< orphan*/  MFTContext; } ;
typedef  TYPE_1__* PNTFS_VOLUME_INFO ;
typedef  int /*<<< orphan*/  PNTFS_RECORD ;
typedef  scalar_t__ PNTFS_MFT_RECORD ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NtfsFixupRecord (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int NtfsReadAttribute (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOLEAN NtfsReadMftRecord(PNTFS_VOLUME_INFO Volume, ULONGLONG MFTIndex, PNTFS_MFT_RECORD Buffer)
{
    ULONGLONG BytesRead;

    BytesRead = NtfsReadAttribute(Volume, Volume->MFTContext, MFTIndex * Volume->MftRecordSize, (PCHAR)Buffer, Volume->MftRecordSize);
    if (BytesRead != Volume->MftRecordSize)
        return FALSE;

    /* Apply update sequence array fixups. */
    return NtfsFixupRecord(Volume, (PNTFS_RECORD)Buffer);
}