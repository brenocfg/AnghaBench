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
struct TYPE_4__ {int kind; struct demangle_component* name; } ;
struct TYPE_3__ {TYPE_2__ s_ctor; } ;
struct demangle_component {TYPE_1__ u; int /*<<< orphan*/  type; scalar_t__ d_printing; } ;
typedef  enum gnu_v3_ctor_kinds { ____Placeholder_gnu_v3_ctor_kinds } gnu_v3_ctor_kinds ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_CTOR ; 
 int gnu_v3_complete_object_ctor ; 
 int gnu_v3_object_ctor_group ; 

int
cplus_demangle_fill_ctor (struct demangle_component *p,
                          enum gnu_v3_ctor_kinds kind,
                          struct demangle_component *name)
{
  if (p == NULL
      || name == NULL
      || (int) kind < gnu_v3_complete_object_ctor
      || (int) kind > gnu_v3_object_ctor_group)
    return 0;
  p->d_printing = 0;
  p->type = DEMANGLE_COMPONENT_CTOR;
  p->u.s_ctor.kind = kind;
  p->u.s_ctor.name = name;
  return 1;
}