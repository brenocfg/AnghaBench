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
struct TYPE_4__ {int /*<<< orphan*/  narray; int /*<<< orphan*/  array; } ;
typedef  TYPE_1__ filemap_t ;
typedef  int /*<<< orphan*/  file_entry_t ;

/* Variables and functions */
 TYPE_1__* filemap ; 
 int /*<<< orphan*/  filemap_list_to_array (TYPE_1__*) ; 
 int /*<<< orphan*/  final_filemap_cmp ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
filemap_finalize(void)
{
	filemap_t  *map = filemap;

	filemap_list_to_array(map);
	qsort(map->array, map->narray, sizeof(file_entry_t *),
		  final_filemap_cmp);
}