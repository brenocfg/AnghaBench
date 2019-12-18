#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ NumberOfSymbols; scalar_t__ PointerToSymbolTable; } ;
struct TYPE_5__ {TYPE_1__ FileHeader; } ;
typedef  int /*<<< orphan*/  IMAGE_SYMBOL ;
typedef  TYPE_2__ IMAGE_NT_HEADERS ;
typedef  int DWORD64 ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 

__attribute__((used)) static BOOL pe_is_valid_pointer_table(const IMAGE_NT_HEADERS* nthdr, const void* mapping, DWORD64 sz)
{
    DWORD64     offset;

    /* is the iSym table inside file size ? (including first DWORD of string table, which is its size) */
    offset = (DWORD64)nthdr->FileHeader.PointerToSymbolTable;
    offset += (DWORD64)nthdr->FileHeader.NumberOfSymbols * sizeof(IMAGE_SYMBOL);
    if (offset + sizeof(DWORD) > sz) return FALSE;
    /* is string table (following iSym table) inside file size ? */
    offset += *(DWORD*)((const char*)mapping + offset);
    return offset <= sz;
}