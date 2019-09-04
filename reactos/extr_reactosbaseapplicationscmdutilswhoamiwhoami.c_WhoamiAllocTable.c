#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Rows; int Cols; } ;
typedef  TYPE_1__ WhoamiTable ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  wprintf (char*) ; 

WhoamiTable *WhoamiAllocTable(UINT Rows, UINT Cols)
{
    WhoamiTable *pTable = HeapAlloc(GetProcessHeap(),
                                    HEAP_ZERO_MEMORY,
                                    sizeof(WhoamiTable) + sizeof(LPWSTR) * Rows * Cols);

    // wprintf(L"DEBUG: Allocating %dx%d elem table for printing.\r\n\r\n", Rows, Cols);

    if (!pTable)
    {
        wprintf(L"ERROR: Not enough memory for displaying the table.");
        exit(1);
    }

    pTable->Rows = Rows;
    pTable->Cols = Cols;

    return pTable;
}