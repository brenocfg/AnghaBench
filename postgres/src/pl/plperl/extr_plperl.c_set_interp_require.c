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
 size_t OP_DOFILE ; 
 size_t OP_REQUIRE ; 
 int /*<<< orphan*/ * PL_ppaddr ; 
 int /*<<< orphan*/  pp_require_orig ; 
 int /*<<< orphan*/  pp_require_safe ; 

__attribute__((used)) static void
set_interp_require(bool trusted)
{
	if (trusted)
	{
		PL_ppaddr[OP_REQUIRE] = pp_require_safe;
		PL_ppaddr[OP_DOFILE] = pp_require_safe;
	}
	else
	{
		PL_ppaddr[OP_REQUIRE] = pp_require_orig;
		PL_ppaddr[OP_DOFILE] = pp_require_orig;
	}
}