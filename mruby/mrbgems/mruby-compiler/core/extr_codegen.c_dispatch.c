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
typedef  int uint16_t ;
struct TYPE_4__ {int iseq; int /*<<< orphan*/  pc; int /*<<< orphan*/  lastlabel; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int PEEK_S (int) ; 
 int /*<<< orphan*/  emit_S (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dispatch(codegen_scope *s, uint16_t pos0)
{
  uint16_t newpos;

  s->lastlabel = s->pc;
  newpos = PEEK_S(s->iseq+pos0);
  emit_S(s, pos0, s->pc);
  return newpos;
}