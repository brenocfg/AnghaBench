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
typedef  void* USHORT ;
typedef  int ULONG ;
struct TYPE_3__ {int /*<<< orphan*/ * Buffer; void* MaximumLength; void* Length; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PSAM_DB_OBJECT ;
typedef  TYPE_1__* PRPC_UNICODE_STRING ;
typedef  int NTSTATUS ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  NT_SUCCESS (int) ; 
 int STATUS_BUFFER_OVERFLOW ; 
 int STATUS_INSUFFICIENT_RESOURCES ; 
 int STATUS_SUCCESS ; 
 int SampGetObjectAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/ * midl_user_allocate (int) ; 
 int /*<<< orphan*/  midl_user_free (int /*<<< orphan*/ *) ; 

NTSTATUS
SampGetObjectAttributeString(PSAM_DB_OBJECT DbObject,
                             LPWSTR AttributeName,
                             PRPC_UNICODE_STRING String)
{
    ULONG Length = 0;
    NTSTATUS Status;

    Status = SampGetObjectAttribute(DbObject,
                                    AttributeName,
                                    NULL,
                                    NULL,
                                    &Length);
    if (!NT_SUCCESS(Status) && Status != STATUS_BUFFER_OVERFLOW)
    {
        TRACE("Status 0x%08lx\n", Status);
        goto done;
    }

    if (Length == 0)
    {
        String->Length = 0;
        String->MaximumLength = 0;
        String->Buffer = NULL;

        Status = STATUS_SUCCESS;
        goto done;
    }

    String->Length = (USHORT)(Length - sizeof(WCHAR));
    String->MaximumLength = (USHORT)Length;
    String->Buffer = midl_user_allocate(Length);
    if (String->Buffer == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto done;
    }

    TRACE("Length: %lu\n", Length);
    Status = SampGetObjectAttribute(DbObject,
                                    AttributeName,
                                    NULL,
                                    (PVOID)String->Buffer,
                                    &Length);
    if (!NT_SUCCESS(Status))
    {
        TRACE("Status 0x%08lx\n", Status);
        goto done;
    }

done:
    if (!NT_SUCCESS(Status))
    {
        if (String->Buffer != NULL)
        {
            midl_user_free(String->Buffer);
            String->Buffer = NULL;
        }
    }

    return Status;
}