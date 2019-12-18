#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_2__ {int /*<<< orphan*/ * lpTable; } ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,size_t) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MCI_END_COMMAND ; 
 scalar_t__ MCI_END_COMMAND_LIST ; 
 int /*<<< orphan*/  MCI_IsCommandTableValid (size_t) ; 
 TYPE_1__* S_MciCmdTable ; 
 int /*<<< orphan*/  TRUE ; 
 int strlenW (scalar_t__) ; 

__attribute__((used)) static	BOOL		MCI_DumpCommandTable(UINT uTbl)
{
    const BYTE*	lmem;
    LPCWSTR	str;
    DWORD	flg;
    WORD	eid;

    if (!MCI_IsCommandTableValid(uTbl)) {
	ERR("Ooops: %d is not valid\n", uTbl);
	return FALSE;
    }

    lmem = S_MciCmdTable[uTbl].lpTable;
    do {
	do {
	    str = (LPCWSTR)lmem;
	    lmem += (strlenW(str) + 1) * sizeof(WCHAR);
	    flg = *(const DWORD*)lmem;
	    eid = *(const WORD*)(lmem + sizeof(DWORD));
            /* TRACE("cmd=%s %08lx %04x\n", debugstr_w(str), flg, eid); */
	    lmem += sizeof(DWORD) + sizeof(WORD);
	} while (eid != MCI_END_COMMAND && eid != MCI_END_COMMAND_LIST);
        /* EPP TRACE(" => end of command%s\n", (eid == MCI_END_COMMAND_LIST) ? " list" : ""); */
    } while (eid != MCI_END_COMMAND_LIST);
    return TRUE;
}