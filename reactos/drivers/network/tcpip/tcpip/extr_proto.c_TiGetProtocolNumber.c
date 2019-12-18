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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_3__ {int* Buffer; } ;
typedef  int* PWSTR ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  RtlUnicodeStringToInteger (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

NTSTATUS TiGetProtocolNumber(
  PUNICODE_STRING FileName,
  PULONG Protocol)
/*
 * FUNCTION: Returns the protocol number from a file name
 * ARGUMENTS:
 *     FileName = Pointer to string with file name
 *     Protocol = Pointer to buffer to put protocol number in
 * RETURNS:
 *     Status of operation
 */
{
  UNICODE_STRING us;
  NTSTATUS Status;
  ULONG Value;
  PWSTR Name;

  TI_DbgPrint(MAX_TRACE, ("Called. FileName (%wZ).\n", FileName));

  Name = FileName->Buffer;

  if (*Name++ != (WCHAR)L'\\')
    return STATUS_UNSUCCESSFUL;

  if (*Name == L'\0')
    return STATUS_UNSUCCESSFUL;

  RtlInitUnicodeString(&us, Name);

  Status = RtlUnicodeStringToInteger(&us, 10, &Value);
  if (!NT_SUCCESS(Status) || ((Value > 255)))
    return STATUS_UNSUCCESSFUL;

  *Protocol = Value;

  return STATUS_SUCCESS;
}