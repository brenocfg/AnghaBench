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
struct TYPE_3__ {scalar_t__ opfuncid; int /*<<< orphan*/  opno; } ;
typedef  TYPE_1__ OpExpr ;

/* Variables and functions */
 scalar_t__ InvalidOid ; 
 scalar_t__ get_opcode (int /*<<< orphan*/ ) ; 

void
set_opfuncid(OpExpr *opexpr)
{
	if (opexpr->opfuncid == InvalidOid)
		opexpr->opfuncid = get_opcode(opexpr->opno);
}