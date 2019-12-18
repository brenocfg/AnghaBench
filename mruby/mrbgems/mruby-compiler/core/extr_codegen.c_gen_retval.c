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
struct TYPE_4__ {int /*<<< orphan*/  car; } ;
typedef  TYPE_1__ node ;
typedef  int /*<<< orphan*/  codegen_scope ;

/* Variables and functions */
 scalar_t__ NODE_SPLAT ; 
 int /*<<< orphan*/  OP_ARYDUP ; 
 int /*<<< orphan*/  VAL ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursp () ; 
 int /*<<< orphan*/  genop_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop () ; 

__attribute__((used)) static void
gen_retval(codegen_scope *s, node *tree)
{
  if (nint(tree->car) == NODE_SPLAT) {
    codegen(s, tree, VAL);
    pop();
    genop_1(s, OP_ARYDUP, cursp());
  }
  else {
    codegen(s, tree, VAL);
    pop();
  }
}