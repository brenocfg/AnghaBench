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
struct handle_table_entry {unsigned int iNextFree; int /*<<< orphan*/ * pObject; } ;
struct handle_table {unsigned int iEntries; struct handle_table_entry* paEntries; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct handle_table_entry* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct handle_table_entry*) ; 
 unsigned int TABLE_SIZE_INCREMENT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (struct handle_table_entry*,struct handle_table_entry*,int) ; 

__attribute__((used)) static BOOL grow_handle_table(struct handle_table *lpTable)
{
    struct handle_table_entry *newEntries;
    unsigned int i, newIEntries;

    newIEntries = lpTable->iEntries + TABLE_SIZE_INCREMENT;

    newEntries = HeapAlloc(GetProcessHeap(), 0, sizeof(struct handle_table_entry)*newIEntries);
    if (!newEntries)
        return FALSE;

    if (lpTable->paEntries)
    {
        memcpy(newEntries, lpTable->paEntries, sizeof(struct handle_table_entry)*lpTable->iEntries);
        HeapFree(GetProcessHeap(), 0, lpTable->paEntries);
    }

    for (i=lpTable->iEntries; i<newIEntries; i++)
    {
        newEntries[i].pObject = NULL;
        newEntries[i].iNextFree = i+1;
    }

    lpTable->paEntries = newEntries;
    lpTable->iEntries = newIEntries;

    return TRUE;
}