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

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  FREETMPS ; 
 int /*<<< orphan*/  G_SCALAR ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  PUSHMARK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTBACK ; 
 int /*<<< orphan*/  SAVETMPS ; 
 int /*<<< orphan*/  SP ; 
 int /*<<< orphan*/  SPAGAIN ; 
 int /*<<< orphan*/  XPUSHs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_pv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dSP ; 
 scalar_t__ get_cv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newSVpv (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv_2mortal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void define_symbolic_field(const char *ev_name,
				  const char *field_name)
{
	dSP;

	ENTER;
	SAVETMPS;
	PUSHMARK(SP);

	XPUSHs(sv_2mortal(newSVpv(ev_name, 0)));
	XPUSHs(sv_2mortal(newSVpv(field_name, 0)));

	PUTBACK;
	if (get_cv("main::define_symbolic_field", 0))
		call_pv("main::define_symbolic_field", G_SCALAR);
	SPAGAIN;
	PUTBACK;
	FREETMPS;
	LEAVE;
}