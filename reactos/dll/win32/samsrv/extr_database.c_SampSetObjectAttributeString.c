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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ USHORT ;
struct TYPE_3__ {scalar_t__ Length; int /*<<< orphan*/ * Buffer; } ;
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  int /*<<< orphan*/  PSAM_DB_OBJECT ;
typedef  TYPE_1__* PRPC_UNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  SampSetObjectAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

NTSTATUS
SampSetObjectAttributeString(PSAM_DB_OBJECT DbObject,
                             LPWSTR AttributeName,
                             PRPC_UNICODE_STRING String)
{
    PWCHAR Buffer = NULL;
    USHORT Length = 0;

    if ((String != NULL) && (String->Buffer != NULL))
    {
        Buffer = String->Buffer;
        Length = String->Length + sizeof(WCHAR);
    }

    return SampSetObjectAttribute(DbObject,
                                  AttributeName,
                                  REG_SZ,
                                  Buffer,
                                  Length);
}