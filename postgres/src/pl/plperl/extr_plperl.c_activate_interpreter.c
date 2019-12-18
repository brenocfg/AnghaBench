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
struct TYPE_4__ {int /*<<< orphan*/  user_id; int /*<<< orphan*/  interp; } ;
typedef  TYPE_1__ plperl_interp_desc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERL_SET_CONTEXT (int /*<<< orphan*/ ) ; 
 TYPE_1__* plperl_active_interp ; 
 int /*<<< orphan*/  set_interp_require (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
activate_interpreter(plperl_interp_desc *interp_desc)
{
	if (interp_desc && plperl_active_interp != interp_desc)
	{
		Assert(interp_desc->interp);
		PERL_SET_CONTEXT(interp_desc->interp);
		/* trusted iff user_id isn't InvalidOid */
		set_interp_require(OidIsValid(interp_desc->user_id));
		plperl_active_interp = interp_desc;
	}
}