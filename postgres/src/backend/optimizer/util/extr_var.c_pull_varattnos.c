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
struct TYPE_3__ {int /*<<< orphan*/ * varattnos; int /*<<< orphan*/  varno; } ;
typedef  TYPE_1__ pull_varattnos_context ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  pull_varattnos_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
pull_varattnos(Node *node, Index varno, Bitmapset **varattnos)
{
	pull_varattnos_context context;

	context.varattnos = *varattnos;
	context.varno = varno;

	(void) pull_varattnos_walker(node, &context);

	*varattnos = context.varattnos;
}