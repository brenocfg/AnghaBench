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
typedef  struct demangle_component {scalar_t__ type; } const demangle_component ;
struct d_print_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_PACK_EXPANSION ; 
 scalar_t__ DEMANGLE_COMPONENT_TEMPLATE_ARGLIST ; 
 struct demangle_component const* d_find_pack (struct d_print_info*,struct demangle_component const*) ; 
 struct demangle_component const* d_left (struct demangle_component const*) ; 
 scalar_t__ d_pack_length (struct demangle_component const*) ; 
 struct demangle_component const* d_right (struct demangle_component const*) ; 

__attribute__((used)) static int
d_args_length (struct d_print_info *dpi, const struct demangle_component *dc)
{
  int count = 0;
  for (; dc && dc->type == DEMANGLE_COMPONENT_TEMPLATE_ARGLIST;
       dc = d_right (dc))
    {
      struct demangle_component *elt = d_left (dc);
      if (elt == NULL)
	break;
      if (elt->type == DEMANGLE_COMPONENT_PACK_EXPANSION)
	{
	  struct demangle_component *a = d_find_pack (dpi, d_left (elt));
	  count += d_pack_length (a);
	}
      else
	++count;
    }
  return count;
}