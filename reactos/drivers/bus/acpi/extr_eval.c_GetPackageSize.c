#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
typedef  size_t UINT32 ;
struct TYPE_10__ {size_t Count; TYPE_3__* Elements; } ;
struct TYPE_11__ {TYPE_4__ Package; } ;
struct TYPE_8__ {int /*<<< orphan*/  Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_7__ {int /*<<< orphan*/  Value; } ;
struct TYPE_9__ {int Type; TYPE_2__ String; TYPE_1__ Integer; } ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_5__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_METHOD_ARGUMENT ;

/* Variables and functions */
#define  ACPI_TYPE_INTEGER 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  DPRINT (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 

__attribute__((used)) static
NTSTATUS
GetPackageSize(ACPI_OBJECT *Package,
               PULONG Count,
               PULONG Size)
{
    ULONG Length, RawLength, TotalLength;
    UINT32 i;

    TotalLength = 0;
    for (i = 0; i < Package->Package.Count; i++)
    {
        switch (Package->Package.Elements[i].Type)
        {
            case ACPI_TYPE_INTEGER:
                Length = sizeof(ACPI_METHOD_ARGUMENT);
                DPRINT("Integer %lu -> %lu: %lu\n", sizeof(ULONG), Length, Package->Package.Elements[i].Integer.Value);
                TotalLength += Length;
                break;

            case ACPI_TYPE_STRING:
                RawLength = Package->Package.Elements[i].String.Length + 1;
                Length = sizeof(ACPI_METHOD_ARGUMENT);
                if (RawLength > sizeof(ULONG))
                    Length += RawLength - sizeof(ULONG);
                DPRINT("String %lu -> %lu: '%s'\n", RawLength, Length, Package->Package.Elements[i].String.Pointer);
                TotalLength += Length;
                break;

            default:
                DPRINT1("Unsupported element type %lu\n", Package->Package.Elements[i].Type);
                return STATUS_UNSUCCESSFUL;
        }
    }

    *Count = Package->Package.Count;
    *Size = TotalLength;

    return STATUS_SUCCESS;
}