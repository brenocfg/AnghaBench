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
typedef  int /*<<< orphan*/  codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  OP_INTERN ; 
 int /*<<< orphan*/  cursp () ; 
 int /*<<< orphan*/  genop_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop () ; 
 int /*<<< orphan*/  push () ; 

__attribute__((used)) static void
gen_intern(codegen_scope *s)
{
  pop();
  genop_1(s, OP_INTERN, cursp());
  push();
}