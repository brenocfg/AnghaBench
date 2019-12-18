#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int args; struct demangle_component* name; } ;
struct TYPE_3__ {TYPE_2__ s_extended_operator; } ;
struct demangle_component {TYPE_1__ u; int /*<<< orphan*/  type; scalar_t__ d_printing; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_EXTENDED_OPERATOR ; 

int
cplus_demangle_fill_extended_operator (struct demangle_component *p, int args,
                                       struct demangle_component *name)
{
  if (p == NULL || args < 0 || name == NULL)
    return 0;
  p->d_printing = 0;
  p->type = DEMANGLE_COMPONENT_EXTENDED_OPERATOR;
  p->u.s_extended_operator.args = args;
  p->u.s_extended_operator.name = name;
  return 1;
}