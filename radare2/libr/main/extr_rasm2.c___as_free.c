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
struct TYPE_4__ {int /*<<< orphan*/  l; int /*<<< orphan*/  anal; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ RAsmState ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_anal_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_asm_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_lib_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __as_free(RAsmState *as) {
	r_asm_free (as->a);
	r_anal_free (as->anal);
	r_lib_free (as->l);
    	free (as);
}