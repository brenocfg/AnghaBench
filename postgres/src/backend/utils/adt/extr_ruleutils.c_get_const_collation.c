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
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ deparse_context ;
struct TYPE_6__ {scalar_t__ constcollid; int /*<<< orphan*/  consttype; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  scalar_t__ Oid ;
typedef  TYPE_2__ Const ;

/* Variables and functions */
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_collation_name (scalar_t__) ; 
 scalar_t__ get_typcollation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_const_collation(Const *constval, deparse_context *context)
{
	StringInfo	buf = context->buf;

	if (OidIsValid(constval->constcollid))
	{
		Oid			typcollation = get_typcollation(constval->consttype);

		if (constval->constcollid != typcollation)
		{
			appendStringInfo(buf, " COLLATE %s",
							 generate_collation_name(constval->constcollid));
		}
	}
}