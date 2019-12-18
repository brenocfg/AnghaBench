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
struct TYPE_6__ {TYPE_1__* ref; } ;
struct TYPE_5__ {scalar_t__ c; struct TYPE_5__* next; int /*<<< orphan*/  type; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ Sym ;
typedef  TYPE_2__ CType ;

/* Variables and functions */
 scalar_t__ FUNC_CALL (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNC_OLD ; 
 int /*<<< orphan*/  is_compatible_parameter_types (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_compatible_types (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_compatible_func(CType *type1, CType *type2) {
	Sym *s1, *s2;

	s1 = type1->ref;
	s2 = type2->ref;
	if (!is_compatible_types (&s1->type, &s2->type)) {
		return 0;
	}
	/* check func_call */
	if (FUNC_CALL (s1->r) != FUNC_CALL (s2->r)) {
		return 0;
	}
	/* XXX: not complete */
	if (s1->c == FUNC_OLD || s2->c == FUNC_OLD) {
		return 1;
	}
	if (s1->c != s2->c) {
		return 0;
	}
	while (s1 != NULL) {
		if (s2 == NULL) {
			return 0;
		}
		if (!is_compatible_parameter_types (&s1->type, &s2->type)) {
			return 0;
		}
		s1 = s1->next;
		s2 = s2->next;
	}
	if (s2) {
		return 0;
	}
	return 1;
}