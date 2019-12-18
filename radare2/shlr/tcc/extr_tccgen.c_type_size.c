#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bits; int /*<<< orphan*/  arch; int /*<<< orphan*/  os; } ;
struct TYPE_7__ {int t; TYPE_1__* ref; } ;
struct TYPE_6__ {int r; int c; TYPE_2__ type; } ;
typedef  TYPE_1__ Sym ;
typedef  TYPE_2__ CType ;

/* Variables and functions */
 int LDOUBLE_ALIGN ; 
 int LDOUBLE_SIZE ; 
 int PTR_SIZE ; 
 int VT_ARRAY ; 
 int VT_BTYPE ; 
 int VT_DOUBLE ; 
 int VT_ENUM ; 
 int VT_FLOAT ; 
 int VT_INT16 ; 
 int VT_INT32 ; 
 int VT_INT64 ; 
 int VT_LDOUBLE ; 
 int VT_PTR ; 
 int VT_QFLOAT ; 
 int VT_QLONG ; 
 scalar_t__ is_structured (TYPE_2__*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__* tcc_state ; 

int type_size(CType *type, int *a) {
	Sym *s;
	int bt;

	bt = type->t & VT_BTYPE;
	if (is_structured(type)) {
		/* struct/union */
		s = type->ref;
		*a = s->r;
		return s->c;
	} else if (bt == VT_PTR) {
		if (type->t & VT_ARRAY) {
			int ts;

			s = type->ref;
			ts = type_size (&s->type, a);

			if (ts < 0 && s->c < 0) {
				ts = -ts;
			}

			return ts * s->c;
		} else {
			*a = PTR_SIZE;
			return PTR_SIZE;
		}
	} else if (bt == VT_LDOUBLE) {
		*a = LDOUBLE_ALIGN;
		return LDOUBLE_SIZE;
	} else if (bt == VT_DOUBLE || bt == VT_INT64) {
		if (!strncmp (tcc_state->arch, "x86", 3) && tcc_state->bits == 32) {
			if (!strncmp (tcc_state->os, "windows", 7)) {
				*a = 8;
			} else {
				*a = 4;
			}
		} else if (!strncmp (tcc_state->arch, "arm", 3)) {
			/* It was like originally:
			        #ifdef TCC_ARM_EABI
			                *a = 8;
			        #else
			        *a = 4;
			        #endif
			        FIXME: Determine EABI then too
			*/
			*a = 8;
		} else {
			*a = 8;
		}
		return 8;
	} else if (bt == VT_ENUM) {
		/* Non standard, but still widely used
		 * and implemented in GCC, MSVC */
		*a = 8;
		return 8;
	} else if (bt == VT_INT32 || bt == VT_FLOAT) {
		*a = 4;
		return 4;
	} else if (bt == VT_INT16) {
		*a = 2;
		return 2;
	} else if (bt == VT_QLONG || bt == VT_QFLOAT) {
		*a = 8;
		return 16;
	} else {
		/* char, void, function, _Bool */
		*a = 1;
		return 1;
	}
}