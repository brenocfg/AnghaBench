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
struct CNDB_Entry {unsigned int ip; char const* name; struct CNDB_Entry* next; } ;
struct TYPE_2__ {struct CNDB_Entry** entries; } ;

/* Variables and functions */
 TYPE_1__* db ; 

__attribute__((used)) static const char *
cndb_lookup(unsigned ip)
{
    const struct CNDB_Entry *entry;
    
    if (db == NULL)
        return 0;

    entry = db->entries[ip&0xFFFF];
    while (entry && entry->ip != ip)
        entry = entry->next;
    if (entry)
        return entry->name;
    else {
        return 0;
    }
}