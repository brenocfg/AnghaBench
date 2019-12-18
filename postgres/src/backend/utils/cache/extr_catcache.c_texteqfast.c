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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2Coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  texteq ; 

__attribute__((used)) static bool
texteqfast(Datum a, Datum b)
{
	/*
	 * The use of DEFAULT_COLLATION_OID is fairly arbitrary here.  We just
	 * want to take the fast "deterministic" path in texteq().
	 */
	return DatumGetBool(DirectFunctionCall2Coll(texteq, DEFAULT_COLLATION_OID, a, b));
}