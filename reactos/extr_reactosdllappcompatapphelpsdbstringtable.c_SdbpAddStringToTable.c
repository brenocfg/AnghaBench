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
struct SdbStringHashTable {int dummy; } ;
struct SdbHashEntry {int /*<<< orphan*/  Tagid; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  TAGID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HashAddString (struct SdbStringHashTable*,struct SdbHashEntry**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct SdbStringHashTable* HashCreate () ; 
 int /*<<< orphan*/  SHIM_ERR (char*) ; 
 struct SdbHashEntry** TableFindPtr (struct SdbStringHashTable*,int /*<<< orphan*/  const*) ; 

BOOL SdbpAddStringToTable(struct SdbStringHashTable** table, const WCHAR* str, TAGID* tagid)
{
    struct SdbHashEntry** entry;

    if (!*table)
    {
        *table = HashCreate();
        if (!*table)
        {
            SHIM_ERR("Error creating hash table\n");
            return FALSE;
        }
    }

    entry = TableFindPtr(*table, str);
    if (*entry)
    {
        *tagid = (*entry)->Tagid;
        return FALSE;
    }
    return HashAddString(*table, entry, str, *tagid);
}