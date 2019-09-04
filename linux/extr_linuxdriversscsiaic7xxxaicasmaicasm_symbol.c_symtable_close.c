#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbol_t ;
typedef  int /*<<< orphan*/  stored_ptr ;
struct TYPE_8__ {scalar_t__ (* seq ) (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* close ) (TYPE_2__*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  R_FIRST ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  symbol_delete (int /*<<< orphan*/ *) ; 
 TYPE_2__* symtable ; 

void
symtable_close()
{
	if (symtable != NULL) {
		DBT	 key;
		DBT	 data;

		while (symtable->seq(symtable, &key, &data, R_FIRST) == 0) {
			symbol_t *stored_ptr;

			memcpy(&stored_ptr, data.data, sizeof(stored_ptr));
			symbol_delete(stored_ptr);
		}
		symtable->close(symtable);
	}
}