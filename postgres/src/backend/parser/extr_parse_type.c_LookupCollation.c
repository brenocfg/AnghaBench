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
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  ParseCallbackState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_parser_errposition_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_collation_oid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setup_parser_errposition_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

Oid
LookupCollation(ParseState *pstate, List *collnames, int location)
{
	Oid			colloid;
	ParseCallbackState pcbstate;

	if (pstate)
		setup_parser_errposition_callback(&pcbstate, pstate, location);

	colloid = get_collation_oid(collnames, false);

	if (pstate)
		cancel_parser_errposition_callback(&pcbstate);

	return colloid;
}