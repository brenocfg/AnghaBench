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
typedef  int /*<<< orphan*/  mrb_code ;
struct TYPE_4__ {int /*<<< orphan*/  pc; int /*<<< orphan*/  lastpc; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  gen_B (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
genop_0(codegen_scope *s, mrb_code i)
{
  s->lastpc = s->pc;
  gen_B(s, i);
}