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
struct CNDB_Entry {unsigned int ip; char* name; struct CNDB_Entry* next; } ;
struct TYPE_3__ {struct CNDB_Entry** entries; } ;

/* Variables and functions */
 TYPE_1__* CALLOC (int,int) ; 
 void* MALLOC (size_t) ; 
 TYPE_1__* db ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,size_t) ; 

__attribute__((used)) static void
cndb_add(unsigned ip, const unsigned char *name, size_t name_length)
{
    struct CNDB_Entry *entry;

    if (name_length == 0)
        return;
    
    if (db == NULL) {
        db = CALLOC(1, sizeof(*db));
    }
        
    entry = MALLOC(sizeof(*entry));
    entry->ip =ip;
    entry->name = MALLOC(name_length+1);
    memcpy(entry->name, name, name_length+1);
    entry->name[name_length] = '\0';
    entry->next = db->entries[ip&0xFFFF];
    db->entries[ip&0xFFFF] = entry;

}