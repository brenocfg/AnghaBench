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
typedef  size_t UINT ;
struct TYPE_2__ {size_t nVerbs; int /*<<< orphan*/ ** aVerbs; int /*<<< orphan*/  lpTable; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;

/* Variables and functions */
 size_t MAX_MCICMDTABLE ; 
 TYPE_1__* S_MciCmdTable ; 
 scalar_t__ strcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static	LPCWSTR		MCI_FindCommand(UINT uTbl, LPCWSTR verb)
{
    UINT	idx;

    if (uTbl >= MAX_MCICMDTABLE || !S_MciCmdTable[uTbl].lpTable)
	return NULL;

    /* another improvement would be to have the aVerbs array sorted,
     * so that we could use a dichotomic search on it, rather than this dumb
     * array look up
     */
    for (idx = 0; idx < S_MciCmdTable[uTbl].nVerbs; idx++) {
	if (strcmpiW(S_MciCmdTable[uTbl].aVerbs[idx], verb) == 0)
	    return S_MciCmdTable[uTbl].aVerbs[idx];
    }

    return NULL;
}