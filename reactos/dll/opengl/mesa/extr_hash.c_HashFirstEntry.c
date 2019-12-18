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
struct HashTable {TYPE_1__** Table; } ;
struct TYPE_2__ {size_t Key; } ;
typedef  size_t GLuint ;

/* Variables and functions */
 size_t TABLE_SIZE ; 
 int /*<<< orphan*/  assert (struct HashTable const*) ; 

GLuint HashFirstEntry(const struct HashTable *table)
{
   GLuint pos;
   assert(table);
   for (pos=0; pos < TABLE_SIZE; pos++) {
      if (table->Table[pos])
         return table->Table[pos]->Key;
   }
   return 0;
}