#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ deparse_expr_cxt ;
struct TYPE_7__ {scalar_t__ relabelformat; int /*<<< orphan*/  resulttypmod; int /*<<< orphan*/  resulttype; int /*<<< orphan*/  arg; } ;
typedef  TYPE_2__ RelabelType ;

/* Variables and functions */
 scalar_t__ COERCE_IMPLICIT_CAST ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deparseExpr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  deparse_type_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
deparseRelabelType(RelabelType *node, deparse_expr_cxt *context)
{
	deparseExpr(node->arg, context);
	if (node->relabelformat != COERCE_IMPLICIT_CAST)
		appendStringInfo(context->buf, "::%s",
						 deparse_type_name(node->resulttype,
										   node->resulttypmod));
}