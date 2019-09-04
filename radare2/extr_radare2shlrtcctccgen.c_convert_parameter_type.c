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
struct TYPE_4__ {int t; } ;
typedef  TYPE_1__ CType ;

/* Variables and functions */
 int VT_ARRAY ; 
 int VT_BTYPE ; 
 int VT_CONSTANT ; 
 int VT_FUNC ; 
 int VT_VOLATILE ; 
 int /*<<< orphan*/  mk_pointer (TYPE_1__*) ; 

__attribute__((used)) static inline void convert_parameter_type(CType *pt) {
	/* remove const and volatile qualifiers (XXX: const could be used
	   to indicate a const function parameter */
	pt->t &= ~(VT_CONSTANT | VT_VOLATILE);
	/* array must be transformed to pointer according to ANSI C */
	pt->t &= ~VT_ARRAY;
	if ((pt->t & VT_BTYPE) == VT_FUNC) {
		mk_pointer (pt);
	}
}