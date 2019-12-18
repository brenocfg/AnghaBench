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
typedef  int UCHAR ;
struct TYPE_3__ {scalar_t__ DllBase; int /*<<< orphan*/  BaseDllName; } ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  Replacement3 ;
typedef  int /*<<< orphan*/  Replacement2 ;
typedef  int /*<<< orphan*/  Replacement1 ;
typedef  TYPE_1__* PLDR_DATA_TABLE_ENTRY ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  Match3 ;
typedef  int /*<<< orphan*/  Match2 ;
typedef  int /*<<< orphan*/  Match1 ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtFlushInstructionCache (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  NtReadVirtualMemory (int /*<<< orphan*/ ,scalar_t__,int*,int,int*) ; 
 scalar_t__ OFFSET_1 ; 
 scalar_t__ OFFSET_2 ; 
 scalar_t__ OFFSET_3 ; 
 int /*<<< orphan*/  Write (scalar_t__,int*,int) ; 
 scalar_t__ memcmp (int*,int const*,int) ; 

__attribute__((used)) static void FixupDll(PLDR_DATA_TABLE_ENTRY LdrEntry)
{
    static const UCHAR Match1[5] = { 0x0C, 0x8B, 0xFC, 0xF3, 0xA5 };
    static const UCHAR Match2[5] = { 0x0C, 0x8B, 0xFC, 0xF3, 0xA5 };
    static const UCHAR Match3[5] = { 0xB0, 0x8B, 0xFC, 0xF3, 0xA5 };
    UCHAR Replacement1[5] = { 0x10, 0x89, 0x34, 0x24, 0x90 };
    UCHAR Replacement2[5] = { 0x10, 0x89, 0x34, 0x24, 0x90 };
    UCHAR Replacement3[5] = { 0xB4, 0x89, 0x34, 0x24, 0x90 };
#define OFFSET_1    0x21A6E
#define OFFSET_2    0x21B04
#define OFFSET_3    0x21C3C


    UCHAR Buffer[5];
    PBYTE Base = LdrEntry->DllBase;
    SIZE_T Bytes;

    /*
    00020E6E: 0C 8B FC F3 A5 --> 10 89 34 24 90     F11A6E - ef0000 = 21A6E
    00020F04: 0C 8B FC F3 A5 --> 10 89 34 24 90     F11B04 - ef0000 = 21B04
    00021C3C: B0 8B FC F3 A5 --> B4 89 34 24 90     F11C3C - ef0000 = 21C3C
    */
    do {
        DbgPrint("Module %wZ Loaded at 0x%p, we should patch!\n", &LdrEntry->BaseDllName, LdrEntry->DllBase);
        if (!NT_SUCCESS(NtReadVirtualMemory(NtCurrentProcess(), Base + OFFSET_1, Buffer, 5, &Bytes)) || Bytes != 5)
            break;
        if (memcmp(Buffer, Match1, sizeof(Match1)))
            break;

        if (!NT_SUCCESS(NtReadVirtualMemory(NtCurrentProcess(), Base + OFFSET_2, Buffer, 5, &Bytes)) || Bytes != 5)
            break;
        if (memcmp(Buffer, Match2, sizeof(Match2)))
            break;

        if (!NT_SUCCESS(NtReadVirtualMemory(NtCurrentProcess(), Base + OFFSET_3, Buffer, 5, &Bytes)) || Bytes != 5)
            break;
        if (memcmp(Buffer, Match3, sizeof(Match3)))
            break;

        DbgPrint("Module %wZ Loaded at 0x%p, OK to patch!\n", &LdrEntry->BaseDllName, LdrEntry->DllBase);
        if (!Write(Base + OFFSET_1, Replacement1, sizeof(Replacement1)))
            break;
        if (!Write(Base + OFFSET_2, Replacement2, sizeof(Replacement2)))
            break;
        if (!Write(Base + OFFSET_3, Replacement3, sizeof(Replacement3)))
            break;

        NtFlushInstructionCache(NtCurrentProcess(), Base, 0x22000);

        DbgPrint("Module %wZ Loaded at 0x%p, patched!\n", &LdrEntry->BaseDllName, LdrEntry->DllBase);
    } while (0);
}