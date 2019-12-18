#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nlist; int narray; int /*<<< orphan*/ * last; TYPE_2__* first; TYPE_2__** array; } ;
typedef  TYPE_1__ filemap_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ file_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ pg_realloc (TYPE_2__**,int) ; 

__attribute__((used)) static void
filemap_list_to_array(filemap_t *map)
{
	int			narray;
	file_entry_t *entry,
			   *next;

	map->array = (file_entry_t **)
		pg_realloc(map->array,
				   (map->nlist + map->narray) * sizeof(file_entry_t *));

	narray = map->narray;
	for (entry = map->first; entry != NULL; entry = next)
	{
		map->array[narray++] = entry;
		next = entry->next;
		entry->next = NULL;
	}
	Assert(narray == map->nlist + map->narray);
	map->narray = narray;
	map->nlist = 0;
	map->first = map->last = NULL;
}