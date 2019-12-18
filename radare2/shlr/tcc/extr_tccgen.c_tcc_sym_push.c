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
struct TYPE_4__ {int t; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ CType ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sym_malloc () ; 
 int /*<<< orphan*/  sym_push (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tcc_sym_push(char *typename, int typesize, int meta) {
	CType *new_type = (CType *) malloc (sizeof(CType));
	if (!new_type) {
		return 0;
	}
	new_type->ref = sym_malloc ();
	new_type->t = meta;

	if (!sym_push (0, new_type, 0, 0)) {
		return 0;
	}

	free (new_type);
	return 1;
}