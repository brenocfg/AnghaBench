#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Buffer; } ;
struct TYPE_9__ {TYPE_1__ Str; } ;
typedef  TYPE_2__* PSDB_TMP_STR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SdbpBuildSignMediaId (TYPE_2__*) ; 
 int /*<<< orphan*/  SdbpFreeTempStr (TYPE_2__*) ; 
 int /*<<< orphan*/  SdbpGetLongPathName (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SdbpInitTempStr (TYPE_2__*) ; 
 scalar_t__ SdbpIsPathOnRemovableMedia (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL SdbpResolvePath(PSDB_TMP_STR LongPath, PCWSTR wszPath)
{
    SdbpInitTempStr(LongPath);
    if (!SdbpGetLongPathName(wszPath, LongPath))
    {
        SdbpFreeTempStr(LongPath);
        return FALSE;
    }
    if (SdbpIsPathOnRemovableMedia(LongPath->Str.Buffer))
    {
        return SdbpBuildSignMediaId(LongPath);
    }
    return TRUE;
}