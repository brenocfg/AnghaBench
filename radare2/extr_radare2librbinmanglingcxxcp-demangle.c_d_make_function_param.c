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
struct TYPE_3__ {int number; } ;
struct TYPE_4__ {TYPE_1__ s_number; } ;
struct demangle_component {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct d_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_FUNCTION_PARAM ; 
 struct demangle_component* d_make_empty (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_make_function_param (struct d_info *di, int i)
{
  struct demangle_component *p;

  p = d_make_empty (di);
  if (p != NULL)
    {
      p->type = DEMANGLE_COMPONENT_FUNCTION_PARAM;
      p->u.s_number.number = i;
    }
  return p;
}