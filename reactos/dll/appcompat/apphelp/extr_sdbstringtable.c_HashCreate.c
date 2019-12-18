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
struct SdbStringHashTable {int Size; void* Entries; } ;

/* Variables and functions */
 int DEFAULT_TABLE_SIZE ; 
 int /*<<< orphan*/  SHIM_ERR (char*) ; 
 void* SdbAlloc (int) ; 

__attribute__((used)) static struct SdbStringHashTable* HashCreate(void)
{
    struct SdbStringHashTable* tab = SdbAlloc(sizeof(*tab));
    if (!tab)
    {
        SHIM_ERR("Failed to allocate 8 bytes.\r\n");
        return tab;
    }
    tab->Size = DEFAULT_TABLE_SIZE;
    tab->Entries = SdbAlloc(tab->Size * sizeof(*tab->Entries));
    return tab;
}