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
struct demangle_component {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_TEMPLATE_ARGLIST ; 
 struct demangle_component* d_left (struct demangle_component*) ; 
 struct demangle_component* d_right (struct demangle_component*) ; 

__attribute__((used)) static struct demangle_component *
d_index_template_argument (struct demangle_component *args, int i)
{
  struct demangle_component *a;

  if (i < 0)
    /* Print the whole argument pack.  */
    return args;

  for (a = args;
       a != NULL;
       a = d_right (a))
    {
      if (a->type != DEMANGLE_COMPONENT_TEMPLATE_ARGLIST)
	return NULL;
      if (i <= 0)
	break;
      --i;
    }
  if (i != 0 || a == NULL)
    return NULL;

  return d_left (a);
}