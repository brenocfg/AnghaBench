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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RStack ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  Fhandled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  r_stack_push (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sdb_num_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdb_num_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void addTarget(RCore *core, RStack *stack, Sdb *db, ut64 addr) {
	if (!sdb_num_get (db, Fhandled(addr), NULL)) {
		ut64* value = (ut64*) malloc (1 * sizeof (ut64));
		if (!value) {
			eprintf ("Failed to allocate memory for address stack\n");
			return;
		}
		*value = addr;
		if (!r_stack_push (stack, (void*)value)) {
			eprintf ("Failed to push address on stack\n");
			free (value);
			return;
		}
		sdb_num_set (db, Fhandled (addr), 1, 0);
	}
}