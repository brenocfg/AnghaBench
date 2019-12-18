#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ fn_refcount; int /*<<< orphan*/  fn_cxt; scalar_t__ reference; int /*<<< orphan*/ * interp; } ;
typedef  TYPE_1__ plperl_proc_desc ;
typedef  int /*<<< orphan*/  plperl_interp_desc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SvREFCNT_dec_current (scalar_t__) ; 
 int /*<<< orphan*/  activate_interpreter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * plperl_active_interp ; 

__attribute__((used)) static void
free_plperl_function(plperl_proc_desc *prodesc)
{
	Assert(prodesc->fn_refcount == 0);
	/* Release CODE reference, if we have one, from the appropriate interp */
	if (prodesc->reference)
	{
		plperl_interp_desc *oldinterp = plperl_active_interp;

		activate_interpreter(prodesc->interp);
		SvREFCNT_dec_current(prodesc->reference);
		activate_interpreter(oldinterp);
	}
	/* Release all PG-owned data for this proc */
	MemoryContextDelete(prodesc->fn_cxt);
}