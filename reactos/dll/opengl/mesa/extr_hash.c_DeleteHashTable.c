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
struct HashTable {struct HashTable* Next; struct HashTable** Table; } ;
struct HashEntry {struct HashEntry* Next; struct HashEntry** Table; } ;
typedef  size_t GLuint ;

/* Variables and functions */
 size_t TABLE_SIZE ; 
 int /*<<< orphan*/  assert (struct HashTable*) ; 
 int /*<<< orphan*/  free (struct HashTable*) ; 

void DeleteHashTable(struct HashTable *table)
{
   GLuint i;
   assert(table);
   for (i=0;i<TABLE_SIZE;i++) {
      struct HashEntry *entry = table->Table[i];
      while (entry) {
	 struct HashEntry *next = entry->Next;
	 free(entry);
	 entry = next;
      }
   }
   free(table);
}