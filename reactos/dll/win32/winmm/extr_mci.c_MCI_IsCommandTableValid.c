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
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_2__ {int /*<<< orphan*/ * lpTable; int /*<<< orphan*/  uDevType; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t MAX_MCICMDTABLE ; 
#define  MCI_COMMAND_HEAD 137 
#define  MCI_CONSTANT 136 
#define  MCI_END_COMMAND 135 
#define  MCI_END_COMMAND_LIST 134 
#define  MCI_END_CONSTANT 133 
#define  MCI_FLAG 132 
#define  MCI_INTEGER 131 
#define  MCI_RECT 130 
#define  MCI_RETURN 129 
#define  MCI_STRING 128 
 TYPE_1__* S_MciCmdTable ; 
 int /*<<< orphan*/  TRACE (char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static	BOOL		MCI_IsCommandTableValid(UINT uTbl)
{
    const BYTE* lmem;
    LPCWSTR     str;
    DWORD	flg;
    WORD	eid;
    int		idx = 0;
    BOOL	inCst = FALSE;

    TRACE("Dumping cmdTbl=%d [lpTable=%p devType=%d]\n",
	  uTbl, S_MciCmdTable[uTbl].lpTable, S_MciCmdTable[uTbl].uDevType);

    if (uTbl >= MAX_MCICMDTABLE || !S_MciCmdTable[uTbl].lpTable)
	return FALSE;

    lmem = S_MciCmdTable[uTbl].lpTable;
    do {
        str = (LPCWSTR)lmem;
        lmem += (strlenW(str) + 1) * sizeof(WCHAR);
        flg = *(const DWORD*)lmem;
        eid = *(const WORD*)(lmem + sizeof(DWORD));
        lmem += sizeof(DWORD) + sizeof(WORD);
        idx ++;
        /* TRACE("cmd=%s %08lx %04x\n", debugstr_w(str), flg, eid); */
        switch (eid) {
        case MCI_COMMAND_HEAD:          if (!*str || !flg) return FALSE; idx = 0;		break;	/* check unicity of str in table */
        case MCI_STRING:                if (inCst) return FALSE;				break;
        case MCI_INTEGER:               if (!*str) return FALSE;				break;
        case MCI_END_COMMAND:           if (*str || flg || idx == 0) return FALSE; idx = 0;	break;
        case MCI_RETURN:		if (*str || idx != 1) return FALSE;			break;
        case MCI_FLAG:		        if (!*str) return FALSE;				break;
        case MCI_END_COMMAND_LIST:	if (*str || flg) return FALSE;	idx = 0;		break;
        case MCI_RECT:		        if (!*str || inCst) return FALSE;			break;
        case MCI_CONSTANT:              if (inCst) return FALSE; inCst = TRUE;			break;
        case MCI_END_CONSTANT:	        if (*str || flg || !inCst) return FALSE; inCst = FALSE; break;
        default:			return FALSE;
        }
    } while (eid != MCI_END_COMMAND_LIST);
    return TRUE;
}