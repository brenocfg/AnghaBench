#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int UINT ;
typedef  int /*<<< orphan*/ * PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PINT ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CreateNestedKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int FLG_ADDREG_OVERWRITEONLY ; 
 int /*<<< orphan*/  GetRootKeyByName (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int MAX_INF_STRING_LENGTH ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ SpInfFindFirstLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SpInfFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpInfGetIntField (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SpInfGetStringField (int /*<<< orphan*/ *,int,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  do_reg_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOLEAN
registry_callback(HINF hInf, PCWSTR Section, BOOLEAN Delete)
{
    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING Name, Value;
    PUNICODE_STRING ValuePtr;
    UINT Flags;
    WCHAR Buffer[MAX_INF_STRING_LENGTH];

    INFCONTEXT Context;
    PCWSTR RootKeyName;
    HANDLE RootKeyHandle, KeyHandle;
    BOOLEAN Ok;

    Ok = SpInfFindFirstLine(hInf, Section, NULL, &Context);
    if (!Ok)
        return TRUE; /* Don't fail if the section isn't present */

    for (;Ok; Ok = SpInfFindNextLine(&Context, &Context))
    {
        /* get root */
        if (!SpInfGetStringField(&Context, 1, Buffer, sizeof(Buffer)/sizeof(WCHAR), NULL))
            continue;
        RootKeyHandle = GetRootKeyByName(Buffer, &RootKeyName);
        if (!RootKeyHandle)
            continue;

        /* get key */
        if (!SpInfGetStringField(&Context, 2, Buffer, sizeof(Buffer)/sizeof(WCHAR), NULL))
            *Buffer = 0;

        DPRINT("KeyName: <%S\\%S>\n", RootKeyName, Buffer);

        /* get flags */
        if (!SpInfGetIntField(&Context, 4, (PINT)&Flags))
            Flags = 0;

        DPRINT("Flags: %lx\n", Flags);

        RtlInitUnicodeString(&Name, Buffer);
        InitializeObjectAttributes(&ObjectAttributes,
                                   &Name,
                                   OBJ_CASE_INSENSITIVE,
                                   RootKeyHandle,
                                   NULL);

        if (Delete || (Flags & FLG_ADDREG_OVERWRITEONLY))
        {
            Status = NtOpenKey(&KeyHandle,
                               KEY_ALL_ACCESS,
                               &ObjectAttributes);
            if (!NT_SUCCESS(Status))
            {
                DPRINT1("NtOpenKey(%wZ) failed (Status %lx)\n", &Name, Status);
                continue;  /* ignore if it doesn't exist */
            }
        }
        else
        {
            Status = CreateNestedKey(&KeyHandle,
                                     KEY_ALL_ACCESS,
                                     &ObjectAttributes,
                                     REG_OPTION_NON_VOLATILE);
            if (!NT_SUCCESS(Status))
            {
                DPRINT1("CreateNestedKey(%wZ) failed (Status %lx)\n", &Name, Status);
                continue;
            }
        }

        /* get value name */
        if (SpInfGetStringField(&Context, 3, Buffer, sizeof(Buffer)/sizeof(WCHAR), NULL))
        {
            RtlInitUnicodeString(&Value, Buffer);
            ValuePtr = &Value;
        }
        else
        {
            ValuePtr = NULL;
        }

        /* and now do it */
        if (!do_reg_operation(KeyHandle, ValuePtr, &Context, Flags))
        {
            NtClose(KeyHandle);
            return FALSE;
        }

        NtClose(KeyHandle);
    }

    return TRUE;
}