#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int MaximumLength; scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_6__ {TYPE_1__ Str; } ;
typedef  TYPE_2__* PSDB_TMP_STR ;

/* Variables and functions */
 int /*<<< orphan*/  SdbAlloc (int) ; 
 int /*<<< orphan*/  SdbpFreeTempStr (TYPE_2__*) ; 

void SdbpResizeTempStr(PSDB_TMP_STR String, WORD newLength)
{
    if (newLength > String->Str.MaximumLength)
    {
        SdbpFreeTempStr(String);
        String->Str.MaximumLength = newLength * sizeof(WCHAR);
        String->Str.Buffer = SdbAlloc(String->Str.MaximumLength);
        String->Str.Length = 0;
    }
}