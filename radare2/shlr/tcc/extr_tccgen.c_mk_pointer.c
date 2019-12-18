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
struct TYPE_4__ {int t; int /*<<< orphan*/ * ref; } ;
typedef  int /*<<< orphan*/  Sym ;
typedef  TYPE_1__ CType ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_FIELD ; 
 int VT_PTR ; 
 int VT_TYPE ; 
 int /*<<< orphan*/ * sym_push (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void mk_pointer(CType *type) {
	Sym *s;
	s = sym_push (SYM_FIELD, type, 0, -1);
	if (!s) {
		return;
	}
	type->t = VT_PTR | (type->t & ~VT_TYPE);
	type->ref = s;
}